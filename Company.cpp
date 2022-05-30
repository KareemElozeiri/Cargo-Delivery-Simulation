#ifndef  Comapny_CPP
#define Comapny_CPP

#include "Company.h"


Company::Company() {
	this->TimestepNum = Time();

	this->pUI = new UI;


	//getting the input & output file names from the UI class
	this->inputFileName = this->pUI->GetInputFilePath();
	this->outputFileName = this->pUI->GetOutputFilePath();


	// initialize load function
	this->LoadInputs();

	//to calc num of auto-promoted cargos
	AutoPromotedCargosNum = 0;
}

Company::~Company() {

	// this->SaveOutputs();

	delete this->pUI;

	// Delete The Event List
	Event* EventTempPtr = nullptr;

	this->cleanQueueInnerPointers(this->EventList);
	delete this->EventList;

	// Delete The Cargos Lists
	Node<Cargo*>* CargoNodeTempPtr = nullptr;

	CargoNodeTempPtr = NormalCargoList->GetHead();
	while (CargoNodeTempPtr != nullptr) {
		delete CargoNodeTempPtr->getItem();
		CargoNodeTempPtr = CargoNodeTempPtr->getNext();
	}

	this->cleanQueueInnerPointers(this->SpecialCargoList);
	this->cleanPriorityQueueInnerPointers(this->VIPCargoList);

	delete this->NormalCargoList;
	delete this->SpecialCargoList;
	delete this->VIPCargoList;

	this->cleanQueueInnerPointers(this->DeliveredNormalCargoList);
	this->cleanQueueInnerPointers(this->DeliveredSpecialCargoList);
	this->cleanQueueInnerPointers(this->DeliveredVIPCargoList);


	delete this->DeliveredNormalCargoList;
	delete this->DeliveredSpecialCargoList;
	delete this->DeliveredVIPCargoList;

	// Delete The Trucks Lists
	this->cleanQueueInnerPointers(this->NormalTrucksList);
	this->cleanQueueInnerPointers(this->SpecialTrucksList);
	this->cleanQueueInnerPointers(this->VIPTrucksList);
	
	delete this->NormalTrucksList;
	delete this->SpecialTrucksList;
	delete this->VIPTrucksList;


	// Delete Checkup Trcuks List
	this->cleanQueueInnerPointers(this->InCheckUpNormalTrucks);
	this->cleanQueueInnerPointers(this->InCheckUpSpecialTrucks);
	this->cleanQueueInnerPointers(this->InCheckUpVIPTrucks);

	delete this->InCheckUpNormalTrucks;
	delete this->InCheckUpSpecialTrucks;
	delete this->InCheckUpVIPTrucks;


	// Delete The Maintenance Lists
	this->cleanQueueInnerPointers(this->NormalMaintenanceTrucksList);
	this->cleanQueueInnerPointers(this->SpecialMaintenanceTrucksList);
	this->cleanQueueInnerPointers(this->VIPMaintenanceTrucksList);

	delete this->NormalMaintenanceTrucksList;
	delete this->SpecialMaintenanceTrucksList;
	delete this->VIPMaintenanceTrucksList;

	// Delete The Moving Trukcs Lists
	this->cleanPriorityQueueInnerPointers(this->MovingTrucks);
}

bool Company::CheckExitStatus() {
	
	// check for application status 
	// The simulation function stops when there are no more events and all cargos are in delivered list

	return (
		this->EventList->isEmpty() &&

		this->NormalCargoList->isEmpty()&&
		this->SpecialCargoList->isEmpty() &&
		this->VIPCargoList->isEmpty() &&

		this->MovingTrucks->isEmpty() &&
		this->NormalMaintenanceTrucksList->isEmpty() &&
		this->VIPMaintenanceTrucksList->isEmpty() &&
		this->SpecialMaintenanceTrucksList->isEmpty() 

		//if there a loading or unloading list done, add its condition here.
		//we may need to add intial value to the trucks to make sure they are home
		//can all cargo be delivered and no moving truck and still no exit status???

		//that checks if all cargos are out then checks that aren't moving so that they are home
		);
}

void Company::Simulate() {
	while (true) {
		this->TimestepNum = this->TimestepNum + 1;

		// Execute the upcoming event
		if (this->IsWorkingHours()) {
			this->ExecuteUpcomingEvent();
		}
		// move trucks from checkup to available
		this->MoveCheckUpToAvailable();

		// move trucks from maintenance to available
		this->MoveMaintenanceToAvailable();

		//handling cargos loading into proper trucks
		if (this->IsWorkingHours()) {
			this->LoadVIPCargosToTruck();
			this->LoadSpecialCargosToTruck();
			this->LoadNormalCargosToTruck();
		}

		// Move Trucks to the moving trucks list if applicable
		this->MoveTrucks();

		// applies probability for a truck to fail delivering while moving
		this->ExecuteFailure();

		// Deliver Cargos
		this->DeliverCargos();

		//check for Auto Promote
		if (this->IsWorkingHours()) {
			this->checkForAutoPromote();
		}

		// print current info
		this->UpdateInterface();

		//check break conditions
		if (this->CheckExitStatus())
		{
			this->SaveOutputs();
			this->pUI->PrintMsg("Simulation is done.");
			break;
		}
	}
}

void Company::LoadInputs() {
	using std::ifstream;
	ifstream inputFile(this->inputFileName);

	//checking that the stream open successfully 
	if (!inputFile.is_open()) {
		this->pUI->PrintMsg("*** Error: Could not open " + this->inputFileName + " ***");
		exit(1);
	}

	/////////////////// Loading Trucks //////////////////////////

	int nTrucksNum, sTrucksNum, vTrucksNum;
	double nTruckSpeed, sTruckSpeed, vTruckSpeed;
	int nCapacity, sCapacity, vCapacity;
	int JourNum;
	int nCheckUpHours, sCheckUpHours, vCheckUpHours;

	//reading parameters from the file 
	inputFile >> nTrucksNum >> sTrucksNum >> vTrucksNum;
	inputFile >> nTruckSpeed >> sTruckSpeed >> vTruckSpeed;
	inputFile >> nCapacity >> sCapacity >> vCapacity;

	inputFile >> JourNum;
	inputFile >> nCheckUpHours >> sCheckUpHours >> vCheckUpHours;


	//adding VIP trucks
	for (int i = 0; i < vTrucksNum; i++)
		this->AddTruck(TRUCKTYPE::VT, vCapacity, Time(vCheckUpHours), JourNum, vTruckSpeed, i);

	//adding special trucks
	for (int i = 0; i < sTrucksNum; i++)
		this->AddTruck(TRUCKTYPE::ST, sCapacity, Time(sCheckUpHours), JourNum, sTruckSpeed, i);

	//adding normal trucks
	for (int i = 0; i < sTrucksNum; i++)
		this->AddTruck(TRUCKTYPE::NT, nCapacity, Time(nCheckUpHours), JourNum, nTruckSpeed, i);


	////////////////// Reading Auto Promotion Limit & Maximum waiting hours ////////////////
	int Apl, MaxW;
	inputFile >> Apl >> MaxW;

	this->AutoPromotionLimit = Time(Apl, 0);
	this->MaxWaitingTime = Time(MaxW);


	///////////////// Loading events ///////////////////

	//reading events from the file




	
	/// loops on each event and takes the letter to check which event function to call.
	/// based on this the event function will take the right number of params for it
	/// Ready : 6 params
	/// Cancellation: 2 params
	/// Promotional: 3 params

	/// <summary>
	/// This reads Line 8 in input file
	/// Based on the number of file there will be number of loops below
	/// </summary>
	inputFile >> NumOfEvents;

	for (int i = 0; i < NumOfEvents; i++) {
		char EventChar;
		inputFile >> EventChar;

		/// <summary>
		/// based on the the first letter in the line, it will go on the corresponding function.
		/// it will continue reading the file by passing the file by reference.
		/// </summary>
		switch (EventChar)
		{
		case 'R':
			ReadReadyEvent(inputFile);
			break;
		case 'P':
			ReadPromotionEvent(inputFile);
			break;
		case 'X':
			ReadCancellationEvent(inputFile);
			break;
		}

	}

	this->pUI->PrintMsg("Input file successfully loaded!");
	inputFile.close();
}


/// These function will continue reading from the file

void Company::ReadReadyEvent(std::ifstream& inputFile)
{
	char sCType;
	inputFile >> sCType;
	CARGOTYPE CType;
	if (sCType == 'N')
		CType = CARGOTYPE::N;
	else if (sCType == 'V')
		CType = CARGOTYPE::V;
	else if (sCType == 'S')
		CType = CARGOTYPE::S;

	string sEventTime;
	inputFile >> sEventTime;
	Time EventTime = splitTime(sEventTime);

	int ID;
	inputFile >> ID;
	int Distance;
	inputFile >> Distance;
	int LT;
	inputFile >> LT;
	int Cost;
	inputFile >> Cost;


	Event* pEvent = new ReadyEvent(this, EventTime, ID, CType, Distance, LT, Cost);
	this->AddEvent(pEvent);
}

void Company::ReadCancellationEvent(std::ifstream& inputFile)
{
	string sEventTime;
	inputFile >> sEventTime;
	string TimeList[2];

	Time EventTime = splitTime(sEventTime);

	int ID;
	inputFile >> ID;
	Event* pEvent = new CancellationEvent(this, EventTime, ID);
	this->AddEvent(pEvent);
}

void Company::ReadPromotionEvent(std::ifstream& inputFile)
{
	string sEventTime;
	inputFile >> sEventTime;
	string TimeList[2];

	Time EventTime = splitTime(sEventTime);

	int ID;
	inputFile >> ID;
	float ExtraMoney;
	inputFile >> ExtraMoney;
	Event* pEvent = new PromotionEvent(this, EventTime, ID, ExtraMoney);
	this->AddEvent(pEvent);
}


CARGOTYPE whichIsFirst(Cargo* c1, Cargo* c2, Cargo* c3) {


	if (c1 == nullptr && c2 != nullptr && c3 != nullptr) {
		if (c2->GetDeliveredTime() < c3->GetDeliveredTime())
			return c2->GetType();
		else
			return c3->GetType();

	}

	else if (c2 == nullptr && c1 != nullptr && c3 != nullptr) {
		if (c1->GetDeliveredTime() < c3->GetDeliveredTime())
			return c1->GetType();
		else
			return c3->GetType();

	}

	else if (c3 == nullptr && c1 != nullptr && c2 != nullptr) {
		if (c1->GetDeliveredTime() < c1->GetDeliveredTime())
			return c1->GetType();
		else
			return c2->GetType();

	}

	else if (c1 == nullptr && c2 == nullptr) {
		return c3->GetType();
	}
	else if (c3 == nullptr && c2 == nullptr) {
		return c1->GetType();
	}
	else if (c1 == nullptr && c3 == nullptr) {
		return c2->GetType();
	}

	else {

	
	Cargo* first_delivered_Cargo = c1;
	CARGOTYPE type = c1->GetType();
	
 	if (c2->GetDeliveredTime() < first_delivered_Cargo->GetDeliveredTime()) {
		first_delivered_Cargo = c2;
	}
	if (c3->GetDeliveredTime() < first_delivered_Cargo->GetDeliveredTime()) {
		first_delivered_Cargo = c3;
	}

	return type;

	}
}

/// There was AddEvents function here and I replaced it with ReadEvents
/// purpose: to read from files and then call the Event class
/// if it has different purpose, add it again 

string Company::OutputString() {


	string dataToOutput = "";
	string statisticsStr = "";

	//cargos stats dec
	int NumOfCargos, NumOfNormalCargos, NumOfVIPCargos, NumOfSpecialCargos;
	Time TotalWaitTime;
	int AutoPromotedCargosPercent;

	//trucks stats dec
	int NumOfTrucks, NumOfNormalTrucks, NumOfVIPTrucks, NumOfSpecialTrucks;
	Time TotalActiveTime;	//used to calc avg active time
	Time TotalAllTime;		//used to calc avg active time
	double TruckUtillization;/////////////////////////////////////////////////////////////////calc


	//putting cargo stats data
	NumOfNormalCargos = this->DeliveredNormalCargoList->getCount();
	NumOfSpecialCargos = this->DeliveredSpecialCargoList->getCount();
	NumOfVIPCargos = this->DeliveredVIPCargoList->getCount();
	NumOfCargos = NumOfNormalCargos + NumOfVIPCargos + NumOfVIPCargos;

	if (NumOfCargos == 0)
		AutoPromotedCargosPercent = 0;	//to prevent dividing by zero
	else
		AutoPromotedCargosPercent = AutoPromotedCargosNum / NumOfNormalCargos * 100;


	//putting cargo stats data
	NumOfNormalTrucks = this->NormalTrucksList->getCount();
	NumOfSpecialTrucks = this->SpecialTrucksList->getCount();
	NumOfVIPTrucks = this->VIPTrucksList->getCount();
	NumOfTrucks = NumOfNormalTrucks + NumOfVIPTrucks + NumOfVIPTrucks;


	dataToOutput += "CDT\tID\tPT\tWT\tTID\n";
	while (!DeliveredNormalCargoList->isEmpty() ||
		!DeliveredVIPCargoList->isEmpty() ||
		!DeliveredSpecialCargoList->isEmpty())
	{

		Cargo* normal;
		this->DeliveredNormalCargoList->peek(normal);
		Cargo* vip;
		this->DeliveredVIPCargoList->peek(vip);
		Cargo* special;
		this->DeliveredSpecialCargoList->peek(special);

		CARGOTYPE type = whichIsFirst(normal, vip, special);

		Cargo* cargo;
		switch (type)
		{
		case CARGOTYPE::S:
			this->DeliveredSpecialCargoList->dequeue(cargo);
			break;
		case CARGOTYPE::V:
			this->DeliveredVIPCargoList->dequeue(cargo);
			break;

		default://case CARGOTYPE::N:
			this->DeliveredNormalCargoList->dequeue(cargo);
			break;
		}

		TotalWaitTime = TotalWaitTime + cargo->GetWaitingTime();
		TotalAllTime = TotalAllTime + 1;		///////////////////////////////////need to be calc.
		TotalActiveTime = TotalActiveTime + 1;	///////////////////////////////////need to be calc.

		dataToOutput += cargo->GetDeliveredTime().StringifyTime() + "\t" +
			std::to_string(cargo->GetID()) + "\t" +
			cargo->GetPrepTime().StringifyTime() + "\t" +
			cargo->GetWaitingTime().StringifyTime() + "\t" +
			std::to_string(cargo->GetTruckID()) + "\n" +
			"";
	}

	dataToOutput += "-----------------------------------------\n" ;

	//calculating statistics...
	int totalWaitHours = TotalWaitTime.GetTotalHours();
	Time AverageWaitTime(totalWaitHours / 24, totalWaitHours % 24);



	double AvgActiveTime = TotalActiveTime.GetTotalHours() / TotalAllTime.GetTotalHours() * 100;

	using std::to_string;
	// Cargo statistics
	//line 1
	statisticsStr += "Cargos: " + to_string(NumOfCargos) +
		" [N: " + to_string(NumOfNormalCargos) +
		", S: " + to_string(NumOfSpecialCargos) +
		", V: " + to_string(NumOfVIPCargos) + "]\n";
	//line 2
	statisticsStr += "Cargo Avg Wait = " + AverageWaitTime.StringifyTime() + "\n";
	//line 3
	statisticsStr += "Auto-promoted Cargos = " + to_string(00000000000000000) + "%\n";//////////calc



	//move truck --> loaded and then start move when timestep come
	//timestep
	//delivered cargos


	// Trucks statistics
	//line 1

	statisticsStr += "Trucks: " + to_string(NumOfTrucks) +
		" [N: " + to_string(NumOfNormalTrucks) +
		", S: " + to_string(NumOfSpecialTrucks) +
		", V: " + to_string(NumOfVIPTrucks) + "]\n";
	//line 2
	statisticsStr += "Avg Active time = " + to_string(AvgActiveTime) + "%\n";
	//line 3
	statisticsStr += "Avg utilization = " + to_string(AutoPromotedCargosPercent) + "%";



	this->CargosOutputLines = CargosOutputLines;
	this->statisticsForOutput = statisticsStr;

	////////could be changed to be just set a member Output string
	return (dataToOutput + statisticsStr);


}


void Company::SaveOutputs() {
	// called on exit
	std::ofstream outputFile(this->outputFileName);

	string outputText = this->OutputString();
	outputFile << outputText;

	//outputFile.close();

}

void Company::AddTruck(TRUCKTYPE truck_type, int capacity, Time checkUpTime, int journeysBeforeCheckUp, double speed, int id)
{
	Truck* truck = new Truck(truck_type, capacity, checkUpTime, journeysBeforeCheckUp, speed, id);
	switch (truck_type)
	{
	case TRUCKTYPE::NT:
		this->NormalTrucksList->enqueue(truck);
		break;
	case TRUCKTYPE::ST:
		this->SpecialTrucksList->enqueue(truck);
		break;
	case TRUCKTYPE::VT:
		this->VIPTrucksList->enqueue(truck);
		break;
	}
}

void Company::UpdateInterface() {
	// Run the appropriate interface function based on the current mode.
	switch (this->pUI->GetAppMode())
	{
	case MODE::INTER:
		pUI->InteractiveInterfaceUpdate(this->GetCurrentTime(), this->GetInteractiveModeData());
		break;
	case MODE::STEP:
		pUI->StepInterfaceUpdate(this->GetCurrentTime(), this->GetInteractiveModeData());
		break;
	case MODE::SILENT:
		pUI->SilentInterfaceUpdate();
		break;
	}
}

std::string Company::GetInteractiveModeData() const {
	string interactive_mode_data;
	string separator = "\n--------------------------------------------------\n";

	int WaitingCargosCount, LoadingTrucksCount, EmptyTrucksCount, IncheckUpTrucksCount, InMaintainanceTrucksCount,
		MovingCargosCount, InCheckupTrucksCount, DeliveredCargosCount;

	WaitingCargosCount = this->NormalCargoList->getCount() +
		this->SpecialCargoList->getCount() +
		this->VIPCargoList->getCount();

	LoadingTrucksCount = 0;

	DeliveredCargosCount = this->DeliveredNormalCargoList->getCount() +
		this->DeliveredSpecialCargoList->getCount() +
		this->DeliveredVIPCargoList->getCount();


	// Waiting Cargos Line:
	interactive_mode_data += std::to_string(WaitingCargosCount) + " Waiting Cargos: ";
	if (NormalCargoList->getCount() > 0)
		interactive_mode_data += "[" + this->NormalCargoList->getData() + "] ";
	if (SpecialCargoList->getCount() > 0)
		interactive_mode_data += "(" + this->SpecialCargoList->getData() + ") ";
	if (VIPCargoList->getCount() > 0)
		interactive_mode_data += "{" + this->VIPCargoList->getData() + "}";
	interactive_mode_data += separator;

	// Loading Trucks Line:
	Truck* TempTruck;
	string loading_trucks_line = "";

	this->NormalTrucksList->peek(TempTruck);
	if (TempTruck && TempTruck->GetCargosCount() > 0) {
		loading_trucks_line += TempTruck->GetID();
		loading_trucks_line += "[" + TempTruck->GetCargosData() + "] ";
		LoadingTrucksCount += 1;
	}

	this->SpecialTrucksList->peek(TempTruck);
	if (TempTruck && TempTruck->GetCargosCount() > 0) {
		loading_trucks_line += TempTruck->GetID();
		loading_trucks_line += "(" + TempTruck->GetCargosData() + ") ";
		LoadingTrucksCount += 1;
	}

	this->VIPTrucksList->peek(TempTruck);
	if (TempTruck && TempTruck->GetCargosCount() > 0) {
		loading_trucks_line += TempTruck->GetID();
		loading_trucks_line += "{" + TempTruck->GetCargosData() + "} ";
		LoadingTrucksCount += 1;
	}

	interactive_mode_data += std::to_string(LoadingTrucksCount) + " Loading Trucks: " + loading_trucks_line + separator;

	// Empty Trucks Line:
	string empty_trucks_line = "";
	EmptyTrucksCount = this->NormalTrucksList->getCount() +
		this->SpecialTrucksList->getCount() +
		this->VIPTrucksList->getCount() - LoadingTrucksCount;
	
	Queue<Truck*>* TempTrucksQueue = new Queue<Truck*>;
	while (this->NormalTrucksList->dequeue(TempTruck)) {
		if (TempTruck->GetCargosCount() == 0)
			empty_trucks_line += "[" + std::to_string(TempTruck->GetID()) + "]";
		TempTrucksQueue->enqueue(TempTruck);
	}
	while (TempTrucksQueue->dequeue(TempTruck)) {
		NormalTrucksList->enqueue(TempTruck);
	}

	while (this->SpecialTrucksList->dequeue(TempTruck)) {
		if (TempTruck->GetCargosCount() == 0)
			empty_trucks_line += "(" + std::to_string(TempTruck->GetID()) + ")";
		TempTrucksQueue->enqueue(TempTruck);
	}
	while (TempTrucksQueue->dequeue(TempTruck)) {
		SpecialTrucksList->enqueue(TempTruck);
	}

	while (this->VIPTrucksList->dequeue(TempTruck)) {
		if (TempTruck->GetCargosCount() == 0)
			empty_trucks_line += "{" + std::to_string(TempTruck->GetID()) + "}";
		TempTrucksQueue->enqueue(TempTruck);
	}
	while (TempTrucksQueue->dequeue(TempTruck)) {
		VIPTrucksList->enqueue(TempTruck);
	}

	interactive_mode_data += std::to_string(EmptyTrucksCount) + " Empty Trucks: " + empty_trucks_line + separator;


	// InCheckup Trucks Line:
	string incheckup_trucks_line = "";
	InMaintainanceTrucksCount = this->InCheckUpNormalTrucks->getCount() +
		this->InCheckUpSpecialTrucks->getCount() +
		this->InCheckUpVIPTrucks->getCount();

	while (this->InCheckUpNormalTrucks->dequeue(TempTruck)) {
		if (TempTruck->GetCargosCount() == 0)
			incheckup_trucks_line += "[" + std::to_string(TempTruck->GetID()) + "]";
		TempTrucksQueue->enqueue(TempTruck);
	}
	while (TempTrucksQueue->dequeue(TempTruck)) {
		InCheckUpNormalTrucks->enqueue(TempTruck);
	}

	while (this->InCheckUpSpecialTrucks->dequeue(TempTruck)) {
		if (TempTruck->GetCargosCount() == 0)
			incheckup_trucks_line += "(" + std::to_string(TempTruck->GetID()) + ")";
		TempTrucksQueue->enqueue(TempTruck);
	}
	while (TempTrucksQueue->dequeue(TempTruck)) {
		InCheckUpSpecialTrucks->enqueue(TempTruck);
	}

	while (this->InCheckUpVIPTrucks->dequeue(TempTruck)) {
		if (TempTruck->GetCargosCount() == 0)
			incheckup_trucks_line += "{" + std::to_string(TempTruck->GetID()) + "}";
		TempTrucksQueue->enqueue(TempTruck);
	}
	while (TempTrucksQueue->dequeue(TempTruck)) {
		InCheckUpVIPTrucks->enqueue(TempTruck);
	}

	interactive_mode_data += std::to_string(InMaintainanceTrucksCount) + " In-Checkup Trucks: " + incheckup_trucks_line + separator;

	// InMaintainance Trucks Line:
	string in_maintainance_trucks_line = "";
	IncheckUpTrucksCount = this->NormalMaintenanceTrucksList->getCount() +
		this->SpecialMaintenanceTrucksList->getCount() +
		this->VIPMaintenanceTrucksList->getCount();

	while (this->NormalMaintenanceTrucksList->dequeue(TempTruck)) {
		if (TempTruck->GetCargosCount() == 0)
			in_maintainance_trucks_line += "[" + std::to_string(TempTruck->GetID()) + "]";
		TempTrucksQueue->enqueue(TempTruck);
	}
	while (TempTrucksQueue->dequeue(TempTruck)) {
		NormalMaintenanceTrucksList->enqueue(TempTruck);
	}

	while (this->SpecialMaintenanceTrucksList->dequeue(TempTruck)) {
		if (TempTruck->GetCargosCount() == 0)
			in_maintainance_trucks_line += "(" + std::to_string(TempTruck->GetID()) + ")";
		TempTrucksQueue->enqueue(TempTruck);
	}
	while (TempTrucksQueue->dequeue(TempTruck)) {
		SpecialMaintenanceTrucksList->enqueue(TempTruck);
	}

	while (this->VIPMaintenanceTrucksList->dequeue(TempTruck)) {
		if (TempTruck->GetCargosCount() == 0)
			in_maintainance_trucks_line += "{" + std::to_string(TempTruck->GetID()) + "}";
		TempTrucksQueue->enqueue(TempTruck);
	}
	while (TempTrucksQueue->dequeue(TempTruck)) {
		VIPMaintenanceTrucksList->enqueue(TempTruck);
	}

	interactive_mode_data += std::to_string(IncheckUpTrucksCount) + " In-Maintainance Trucks: " + in_maintainance_trucks_line + separator;


	// Moving Cargo Line:
	string MovingTrucksLine = "";
	MovingCargosCount = 0;
	PQueue<Truck*>* TempMovingTrucks = new PQueue<Truck*>;
	TempTruck = nullptr;

	while (this->MovingTrucks->dequeue(TempTruck)) {
		string TruckOpenBracket = "{";
		string TruckEndBracket = "}";

		switch (TempTruck->GetCargoType())
		{
			case CARGOTYPE::N:
				TruckOpenBracket = "[";
				TruckEndBracket = "]";
				break;
			case CARGOTYPE::S:
				TruckOpenBracket = "(";
				TruckEndBracket = ")";
				break;
		}

		MovingTrucksLine += std::to_string(TempTruck->GetID()) + 
			TruckOpenBracket + 
			TempTruck->GetCargosData() + 
			TruckEndBracket + " ";
		TempMovingTrucks->enqueue(TempTruck, TempTruck->GetTruckPriority());

		MovingCargosCount += TempTruck->GetCargosCount();
	}

	while (TempMovingTrucks->dequeue(TempTruck)) {
		MovingTrucks->enqueue(TempTruck, TempTruck->GetTruckPriority());
	}

	delete TempMovingTrucks;

	MovingTrucksLine = std::to_string(MovingCargosCount) + " Moving Cargos: " + MovingTrucksLine + separator;

	interactive_mode_data += MovingTrucksLine;

	// Delivered Cargos Line:
	interactive_mode_data += std::to_string(DeliveredCargosCount) + " Delivered Cargos: ";
	if (this->DeliveredNormalCargoList->getCount() > 0)
		interactive_mode_data += "[" + this->DeliveredNormalCargoList->getData() + "] ";
	if (this->DeliveredSpecialCargoList->getCount() > 0)
		interactive_mode_data += "(" + this->DeliveredSpecialCargoList->getData() + ") ";
	if (this->DeliveredVIPCargoList->getCount() > 0)
		interactive_mode_data += "{" + this->DeliveredVIPCargoList->getData() + "}";
	interactive_mode_data += separator;

	return interactive_mode_data;
}

void Company::AddEvent(Event* pEvent) {
	this->EventList->enqueue(pEvent);
}

void Company::AddWaitCargo(Cargo* pCargo) {
	CARGOTYPE cargo_type = pCargo->GetType();
	switch (cargo_type)
	{
	case CARGOTYPE::N:
		this->NormalCargoList->Insert(pCargo);
		break;
	case CARGOTYPE::S:
		this->SpecialCargoList->enqueue(pCargo);
		break;
	case CARGOTYPE::V:
		this->AddVIPCargo(pCargo);
		break;

	}
}

Cargo* Company::FindNormalCargo(int ID) {
	Node<Cargo*>* Head = this->NormalCargoList->GetHead();

	while (Head != nullptr) {
		if (Head->getItem()->GetID() == ID) {
			return Head->getItem();
		}
		Head = Head->getNext();
	}

	return nullptr;
}

/*
	- Can be optimized.
*/

void Company::DeleteNormalCargo(int ID) {

	Node<Cargo*>* loopingPtr = this->NormalCargoList->GetHead();
	Node<Cargo*>* prevPtr = loopingPtr;
	if (this->NormalCargoList->GetHead() == loopingPtr) {
		this->NormalCargoList->SetHead(loopingPtr->getNext());
		delete loopingPtr;
		this->NormalCargoList->DecreaseCount();
		loopingPtr = nullptr;
		return;
	}

	while (loopingPtr != nullptr) {
		if (loopingPtr->getItem()->GetID() == ID) {
			prevPtr->setNext(loopingPtr->getNext());
			delete loopingPtr;
			loopingPtr = nullptr;
			return;
		}
	}

}

/*
	- Priority doesn't only depend on the cost. *Need to change*
*/
void Company::AddVIPCargo(Cargo* pCargo) {

	double priority_calc =
		 3 * pCargo->GetCost() / 2000
		-2 * pCargo->GetDeliveryDistance() / 2000
		-1.5 * pCargo->GetPrepTime().GetTotalHours() / 5
		-1.5 * pCargo->GetLoadTime() / 10;


	this->VIPCargoList->enqueue(pCargo, priority_calc);
}

bool Company::ExecuteUpcomingEvent() {
	Event* tempEvent = nullptr;
	this->EventList->peek(tempEvent);
	// checking if there was actually an event to execute next
	if (tempEvent != nullptr) {
		// Total Hours of the Event & Timestep Relative to the Starting Point.
		int EventTotalHours = tempEvent->GetEventTime().GetTotalHours();
		int TimestepTotalHours = TimestepNum.GetTotalHours();
		// Executes the event in case the current time is equal to the event time.
		if (TimestepTotalHours >= EventTotalHours) {
			tempEvent->Execute();
			EventList->dequeue(tempEvent);
			delete tempEvent;
			return true;
		}
	}

	return false;
}

std::string Company::GetCurrentTime() {
	int hours = this->TimestepNum.GetHour();
	int day = this->TimestepNum.GetDay();

	return to_string(day) + ":" + to_string(hours);
}

bool Company::LoadVIPCargosToTruck()
{	

	if (this->VIPCargoList->getCount() != 0) {

		Truck* vipTruck;
		this->VIPTrucksList->peek(vipTruck);

		Truck* normalTruck;
		this->NormalTrucksList->peek(normalTruck);

		Truck* specialTruck;
		this->SpecialTrucksList->peek(specialTruck);

		//checks first for the availability of VIP trucks
		if (vipTruck != nullptr) {
			if (OtherTwoNotWorkingOnThat(specialTruck, normalTruck, CARGOTYPE::V) == true) {
				if ((vipTruck->IsLoading() == false) && (CanTruckLoad(vipTruck, this->VIPCargoList))) {
					vipTruck->SetCargoType(CARGOTYPE::V);
					vipTruck->SetLoading(true);
				}


				if ((vipTruck->IsLoading() == true) && (vipTruck->GetCargoType() == CARGOTYPE::V)) {
					this->LoadTruck(vipTruck, this->VIPCargoList);
					return true;
				}
			}
		}
		else if (this->ForceMoveMaintenanceToAvailable(TRUCKTYPE::VT)) {
			return this->LoadVIPCargosToTruck();
		}

		//checks second for the availability of normal trucks
		if (normalTruck != nullptr) {
			if (OtherTwoNotWorkingOnThat(vipTruck, specialTruck, CARGOTYPE::V)) {
				if ((normalTruck->IsLoading() == false) && (CanTruckLoad(normalTruck, this->VIPCargoList))) {
					normalTruck->SetCargoType(CARGOTYPE::V);
					normalTruck->SetLoading(true);
				}


				if ((normalTruck->IsLoading() == true) && (normalTruck->GetCargoType() == CARGOTYPE::V)) {
					this->LoadTruck(normalTruck, this->VIPCargoList);
					return true;
				}
			}
		}
		else if (this-ForceMoveMaintenanceToAvailable(TRUCKTYPE::NT)) {
			return this->LoadVIPCargosToTruck();
		}

		//checks last for the availability of special trucks
		if (specialTruck != nullptr) {
			if ((specialTruck->IsLoading()==false) && (CanTruckLoad(specialTruck, this->VIPCargoList))) {
				specialTruck->SetCargoType(CARGOTYPE::V);
				specialTruck->SetLoading(true);
			}


			if ((specialTruck->IsLoading()==true) && (specialTruck->GetCargoType() == CARGOTYPE::V)) {
				this->LoadTruck(specialTruck, this->VIPCargoList);
				return true;
			}
		}
		else if (this->ForceMoveMaintenanceToAvailable(TRUCKTYPE::ST)) {
			return this->LoadVIPCargosToTruck();
		}
	}
	return false;
}

bool Company::LoadSpecialCargosToTruck()
{
	if(this->SpecialCargoList->getCount() != 0){
		Truck* specialTruck;
		this->SpecialTrucksList->peek(specialTruck);

		if (specialTruck != nullptr) {
			if ((specialTruck->IsLoading() == false) && (CanTruckLoad(specialTruck, this->SpecialCargoList))) {
				specialTruck->SetCargoType(CARGOTYPE::S);
				specialTruck->SetLoading(true);
			}
			else if ((specialTruck->IsLoading() == false) && (CurrentCargoIsMaxWaiting(this->SpecialCargoList) == true)) {
				specialTruck->SetCargoType(CARGOTYPE::S);

				Cargo* c;
				this->SpecialCargoList->peek(c);

				if (specialTruck->LoadCargo(c)) {
					this->SpecialCargoList->dequeue(c);
				}

				specialTruck->SetLoaded(true);
				specialTruck->SetLoading(false);
				return true;
			}


			if ((specialTruck->IsLoading() == true) && (specialTruck->GetCargoType() == CARGOTYPE::S)) {
				this->LoadTruck(specialTruck, this->SpecialCargoList);
				return true;
			}
		}
		else if (this->ForceMoveMaintenanceToAvailable(TRUCKTYPE::ST)) {
			return this->LoadSpecialCargosToTruck();
		}
	}
	return false;
}

bool Company::LoadNormalCargosToTruck()
{
	if (this->NormalCargoList->getCount() != 0) {
		Truck* normalTruck;
		this->NormalTrucksList->peek(normalTruck);
		Truck* vipTruck;
		this->VIPTrucksList->peek(vipTruck);

		if (normalTruck != nullptr) {

			if ((vipTruck == nullptr) || (vipTruck->IsLoading() == false) || (vipTruck->GetCargoType() != CARGOTYPE::N)) {


				if ((normalTruck->IsLoading() == false) && (CanTruckLoad(normalTruck, this->NormalCargoList))) {

					normalTruck->SetCargoType(CARGOTYPE::N);
					normalTruck->SetLoading(true);
				}
				else if ((normalTruck->IsLoading() == false) && (CurrentCargoIsMaxWaiting(this->NormalCargoList) == true)) {
					normalTruck->SetCargoType(CARGOTYPE::N);


					Cargo* c = this->NormalCargoList->GetHead()->getItem();

					Node<Cargo*>* tempNode = this->NormalCargoList->GetHead();
					if (normalTruck->LoadCargo(c)) {
						this->NormalCargoList->SetHead(tempNode->getNext());
						tempNode->setNext(nullptr);
						delete tempNode;
						this->NormalCargoList->setCount(this->NormalCargoList->getCount() - 1);
					}

					normalTruck->SetLoaded(true);
					normalTruck->SetLoading(false);
					return true;
				}


				if ((normalTruck->IsLoading() == true) && (normalTruck->GetCargoType() == CARGOTYPE::N)) {
					this->LoadTruck(normalTruck, this->NormalCargoList);
					return true;
				}
			}
		}
		else if (this->ForceMoveMaintenanceToAvailable(TRUCKTYPE::NT)) {
			return this->LoadNormalCargosToTruck();
		}

		if (vipTruck != nullptr) {
			if ((!(vipTruck->IsLoading())) && (CanTruckLoad(vipTruck, this->NormalCargoList))) {
				vipTruck->SetCargoType(CARGOTYPE::N);
				vipTruck->SetLoading(true);
			}
			else if ((vipTruck->IsLoading() == false) && (CurrentCargoIsMaxWaiting(this->NormalCargoList) == true)) {

				vipTruck->SetCargoType(CARGOTYPE::N);

				Cargo* c = this->NormalCargoList->GetHead()->getItem();

				Node<Cargo*>* tempNode = this->NormalCargoList->GetHead();
				if (vipTruck->LoadCargo(c)) {
					this->NormalCargoList->SetHead(tempNode->getNext());
					tempNode->setNext(nullptr);
					delete tempNode;
					this->NormalCargoList->setCount(this->NormalCargoList->getCount() - 1);
				}

				vipTruck->SetLoaded(true);
				vipTruck->SetLoading(false);
				return true;
			}


			if ((vipTruck->IsLoading()) && (vipTruck->GetCargoType() == CARGOTYPE::N)) {
				this->LoadTruck(vipTruck, this->NormalCargoList);
				return true;
			}
		}
		else if (this->ForceMoveMaintenanceToAvailable(TRUCKTYPE::VT)) {
			return this->LoadNormalCargosToTruck();
		}
	}
	return false;
}

void Company::LoadTruck(Truck* truck, Queue<Cargo*>* cargoQueue)
{
	Cargo* c;
	cargoQueue->peek(c);
	if (c != nullptr) {
		if (c->GetLoadOnTruckTime() == Time(0, 0))
			c->SetLoadOnTruckTime(Time(c->GetLoadTime()) + this->TimestepNum);

		if (c->GetLoadOnTruckTime() == this->TimestepNum) {
			if ((truck->LoadCargo(c)) == true)
				cargoQueue->dequeue(c);
		}
	}
}

void Company::LoadTruck(Truck* truck, LinkedList<Cargo*>* cargoList)
{
	if (cargoList->GetHead() != nullptr) {
		Cargo* c = cargoList->GetHead()->getItem();
		Node<Cargo*>* tempNode = cargoList->GetHead();
		
		if (c->GetLoadOnTruckTime() == Time(0, 0))
			c->SetLoadOnTruckTime(Time(c->GetLoadTime()) + this->TimestepNum);
		
		if (c->GetLoadOnTruckTime() == this->TimestepNum) {
			if (truck->LoadCargo(c)) {
				cargoList->SetHead(tempNode->getNext());
				tempNode->setNext(nullptr);
				delete tempNode;

				cargoList->setCount(cargoList->getCount() - 1);
			}
		}
	}
}

bool Company::CanTruckLoad(Truck* truck, Queue<Cargo*>* givenQueue)
{
	if (givenQueue->getCount() >= truck->GetCapacity())
		return true;

	return false;
}

bool Company::CanTruckLoad(Truck* truck, LinkedList<Cargo*>* givenList)
{
	if (givenList->getCount() >= truck->GetCapacity())
		return true;

	return false;
}

bool Company::OtherTwoNotWorkingOnThat(Truck* truck1, Truck* truck2, CARGOTYPE c)
{
	if ((truck1 == nullptr) && (truck2 == nullptr))
		return true;
	else if ((truck1 == nullptr))
		if(((truck2->IsLoading() == false) || (truck2->GetCargoType() != c)))
				return true;
	else if ((truck2 == nullptr))
			if ((truck1->IsLoading() == false) || (truck1->GetCargoType() != c))
					return true;
	else if (((truck1->IsLoading() == false) || (truck1->GetCargoType() != c)) && ((truck2->IsLoading() == false) || (truck2->GetCargoType() != c)))
		return true;

	return false;
}

bool Company::CurrentCargoIsMaxWaiting(Queue<Cargo*>* givenQueue)
{
	Cargo* c;
	givenQueue->peek(c);
	if (c != nullptr) {
		Time waitingTime = this->TimestepNum - c->GetPrepTime();
		if (waitingTime >= this->MaxWaitingTime)
			return true;
	}
	return false;
}

bool Company::CurrentCargoIsMaxWaiting(LinkedList<Cargo*>* givenList)
{
	if (givenList->GetHead() != nullptr) {
		Cargo* c;
		c = givenList->GetHead()->getItem();
		if (c != nullptr) {
			Time waitingTime = this->TimestepNum - c->GetPrepTime();
			if (waitingTime >= this->MaxWaitingTime)
				return true;
		}
	}
	return false;
}

bool Company::IsWorkingHours()
{
	return (this->TimestepNum >= Time(this->TimestepNum.GetDay(), 5)) && (this->TimestepNum <= Time(this->TimestepNum.GetDay(), 23));
}


template <typename T>
void Company::cleanQueueInnerPointers(Queue<T*>* queue)
{
	T* tempPointer = nullptr;
	while (queue->dequeue(tempPointer))
	{
		delete tempPointer;
		tempPointer = nullptr;
	}
}

template <typename T>
void Company::cleanPriorityQueueInnerPointers(PQueue<T*>* pqueue)
{
	T* tempPointer = nullptr;
	while (pqueue->dequeue(tempPointer))
	{
		delete tempPointer;
		tempPointer = nullptr;
	}
}


void Company::checkForAutoPromote() {
	Node<Cargo*>* Head = this->NormalCargoList->GetHead();

	while (Head != nullptr) {
		Cargo* pCargo = Head->getItem();
		Time res = (this->TimestepNum - pCargo->GetPrepTime());
		Head = Head->getNext();
		if (this->AutoPromotionLimit <= res) {
			AutoPromote(pCargo);
			AutoPromotedCargosNum += 1;
		}

	}
}

bool Company::isChangeableCargo(int ID) {
	return (this->FindNormalCargo(ID) != nullptr) ? true : false;
}

void Company::AutoPromote(Cargo* pCargo) {
	//if a cargo wait more than auotp days from its preparation time to be assigned to a truck,
	//it should be automatically promoted to be an vip cargo
		 
		this->DeleteNormalCargo(pCargo->GetID());
		this->AddVIPCargo(pCargo);
	
}

void Company::MoveMovingToAvilable()
{



}

void Company::MoveTrucks() {
	Truck* checkingTruck = nullptr;

	this->NormalTrucksList->peek(checkingTruck);
	if (checkingTruck != nullptr) {
		if (checkingTruck->IsLoaded()) {
			NormalTrucksList->dequeue(checkingTruck);
			checkingTruck->SetMovingStartTime(TimestepNum);
			checkingTruck->UpdateTruckPriority();
			MovingTrucks->enqueue(checkingTruck, checkingTruck->GetTruckPriority());
		}
	}

	this->SpecialTrucksList->peek(checkingTruck);
	if (checkingTruck != nullptr) {
		if (checkingTruck->IsLoaded()) {
			SpecialTrucksList->dequeue(checkingTruck);
			checkingTruck->SetMovingStartTime(TimestepNum);
			checkingTruck->UpdateTruckPriority();
			MovingTrucks->enqueue(checkingTruck, checkingTruck->GetTruckPriority());
		}
	}

	this->VIPTrucksList->peek(checkingTruck);
	if (checkingTruck != nullptr) {
		if (checkingTruck->IsLoaded()) {
			VIPTrucksList->dequeue(checkingTruck);
			checkingTruck->SetMovingStartTime(TimestepNum);
			checkingTruck->UpdateTruckPriority();
			MovingTrucks->enqueue(checkingTruck, checkingTruck->GetTruckPriority());
		}
	}
}

bool Company::CheckForCheckUp(Truck* pTruck){
	if (pTruck->GetJourneysBeforeCheckUp() == 0) {
		this->MoveToCheckUp(pTruck);
		return true;
	}
	return false;
}
void Company::MoveToCheckUp(Truck* pTruck) {

	Queue<Truck*>* MaintenanceList;
	Queue<Truck*>* CheckUpList;

	switch (pTruck->GetTruckType())
	{
	case (TRUCKTYPE::NT):
		MaintenanceList = this->NormalMaintenanceTrucksList;
		CheckUpList = this->InCheckUpNormalTrucks;
		break;
	case (TRUCKTYPE::ST):
		MaintenanceList = this->SpecialMaintenanceTrucksList;
		CheckUpList = this->InCheckUpSpecialTrucks;
		break;
	default:
		MaintenanceList = this->VIPMaintenanceTrucksList;
		CheckUpList = this->InCheckUpVIPTrucks;
		break;
	}

	pTruck->ResetJourneysCount();
	Time OutTime = pTruck->GetCheckUpTime() + this->TimestepNum;

	if (this->CheckForMaintenance(pTruck)) {
		OutTime = OutTime + 10;
		pTruck->setCheckUpOutTime(OutTime);
		MaintenanceList->enqueue(pTruck);
	}
	else {
		pTruck->setCheckUpOutTime(OutTime);
		CheckUpList->enqueue(pTruck);
	}

}


void Company::MoveCheckUpToAvailable() {
	Truck* pTruck;

	// Move normal trucks
	while (true) {
		this->InCheckUpNormalTrucks->peek(pTruck);
		if (pTruck == nullptr) break;

		if (pTruck->getCheckUpOutTime() <= this->TimestepNum) {
			pTruck->SetMovingStartTime(NULL);
			this->NormalTrucksList->enqueue(pTruck);
			this->InCheckUpNormalTrucks->dequeue(pTruck);
		}
		else break;
	}

	// Move special trucks
	while (true) {
		this->InCheckUpSpecialTrucks->peek(pTruck);
		if (pTruck == nullptr) break;

		if (pTruck->getCheckUpOutTime() <= this->TimestepNum) {
			pTruck->SetMovingStartTime(NULL);
			this->SpecialTrucksList->enqueue(pTruck);
			this->InCheckUpSpecialTrucks->dequeue(pTruck);
		}
		else break;
	}

	// Move vip trucks
	while (true) {
		this->InCheckUpVIPTrucks->peek(pTruck);
		if (pTruck == nullptr) break;

		if (pTruck->getCheckUpOutTime() <= this->TimestepNum) {
			pTruck->SetMovingStartTime(NULL);
			this->VIPTrucksList->enqueue(pTruck);
			this->InCheckUpVIPTrucks->dequeue(pTruck);
		}
		else break;
	}
}

bool Company::CheckForMaintenance(Truck* pTruck) {
	// maintenance factors ::
	// - checks if truck has completed a total number of journeys more than double of its max checkup journeys

	if (pTruck->GetTotalCompletedJourneys() >= (pTruck->GetMaxJourneysBeforeCheckUp()*2)) {
		return true;
	}
	else {
		return false;
	}
}

void Company::MoveMaintenanceToAvailable() {
	Truck* pTruck;

	// normal truck move to available
	while (true) {
		this->NormalMaintenanceTrucksList->peek(pTruck);
		if (pTruck == nullptr) break;

		if (pTruck->getCheckUpOutTime() <= this->TimestepNum) {
			pTruck->SetMovingStartTime(NULL);
			this->NormalTrucksList->enqueue(pTruck);
			this->NormalMaintenanceTrucksList->dequeue(pTruck);
		}
		else break;
	}

	// special truck move to available
	while (true) {
		this->SpecialMaintenanceTrucksList->peek(pTruck);
		if (pTruck == nullptr) break;

		if (pTruck->getCheckUpOutTime() <= this->TimestepNum) {
			pTruck->SetMovingStartTime(NULL);
			this->SpecialTrucksList->enqueue(pTruck);
			this->SpecialMaintenanceTrucksList->dequeue(pTruck);
		}
		else break;
	}

	// vip truck move to available
	while (true) {
		this->VIPMaintenanceTrucksList->peek(pTruck);
		if (pTruck == nullptr) break;

		if (pTruck->getCheckUpOutTime() <= this->TimestepNum) {
			pTruck->SetMovingStartTime(NULL);
			this->VIPTrucksList->enqueue(pTruck);
			this->VIPMaintenanceTrucksList->dequeue(pTruck);
		}
		else break;
	}
}

void Company::DeliverCargos() {
	Truck* TempTruck = nullptr;
	Cargo* TempCargo = nullptr;

	Queue<Truck*> TempTruckQ;

	while (this->MovingTrucks->dequeue(TempTruck)) {
		bool willDeliver = false;
		TempTruck->PeekCargos(TempCargo);
		while (TempCargo) {
			Time TruckAfterMovingTime(TempCargo->GetDeliveryDistance() / 
				TempTruck->GetSpeed() +
				TempCargo->GetLoadTime());
			if (TruckAfterMovingTime + TempTruck->GetMovingStartTime() == this->TimestepNum) {
				willDeliver = true;
				TempTruck->DequeueTopCargo(TempCargo);
				TempCargo->SetDeliveredTime(this->TimestepNum);
				TempCargo->SetTruckID(TempTruck->GetID());
				switch (TempCargo->GetType())
				{
				case CARGOTYPE::N:
					this->DeliveredNormalCargoList->enqueue(TempCargo);
					break;
				case CARGOTYPE::S:
					this->DeliveredSpecialCargoList->enqueue(TempCargo);
					break;
				case CARGOTYPE::V:
					this->DeliveredVIPCargoList->enqueue(TempCargo);
					break;
				}
			}
			else {
				break;
			}
			TempTruck->PeekCargos(TempCargo);
		}

		// If the Truck delivered all the Cargos.
		if (TempTruck->GetCargosCount() == 0) {
			// Setting the journeys counters.
			TempTruck->IncrementJourneysCompleted();
			TempTruck->DecreaseJourneyBeforeCheckUp();
			TempTruck->SetLoaded(false);
			// Handling the truck location after delivering the cargos.
			if (!this->CheckForCheckUp(TempTruck)) {
				switch (TempTruck->GetTruckType())
				{
				case TRUCKTYPE::NT:
					this->NormalTrucksList->enqueue(TempTruck);
					break;
				case TRUCKTYPE::ST:
					this->SpecialTrucksList->enqueue(TempTruck);
					break;
				case TRUCKTYPE::VT:
					this->VIPTrucksList->enqueue(TempTruck);
					break;
				}
			}
		}
		else {
			TempTruck->UpdateTruckPriority();
			TempTruckQ.enqueue(TempTruck);
		}

		if (!willDeliver) {
			break;
		}
	}

	while (TempTruckQ.dequeue(TempTruck)) {
		this->MovingTrucks->enqueue(TempTruck, TempTruck->GetTruckPriority());
	}
}

void Company::ExecuteFailure() {
	double probability = 0; // probability of dropping a truck
	int numtodrop = 0;

	if (this->MovingTrucks->getCount() == 0) {
		return;
	}

	if ((rand() % 100) < probability) {
		numtodrop = rand() % this->MovingTrucks->getCount() + 1;
		for (int i = 0; i < numtodrop; i++) {
			this->DropTruck();
		}
	}
}

void Company::DropTruck() {
	Truck* pTruck;
	this->MovingTrucks->dequeue(pTruck);
	pTruck->SetLoaded(false);
	
	Cargo* pCargo = nullptr;

	switch (pTruck->GetCargoType())
	{
	case (CARGOTYPE::N):
		while (pTruck->DequeueTopCargo(pCargo)) {
			this->NormalCargoList->Insert(pCargo);
			//pTruck->DequeueTopCargo(pCargo);
		}
		break;
	case (CARGOTYPE::S):
		while (pTruck->DequeueTopCargo(pCargo)) {
			this->SpecialCargoList->enqueue(pCargo);
			//pTruck->DequeueTopCargo(pCargo);
		}
		break;
	case (CARGOTYPE::V):
		while (pTruck->DequeueTopCargo(pCargo)) {
			this->AddVIPCargo(pCargo);
			//pTruck->DequeueTopCargo(pCargo);
		}
		break;
	}

	this->MoveToCheckUp(pTruck);
}

string Company::getStatisticsForOutput()
{
	return this->statisticsForOutput;
}

string Company::getCargoOutputLines()
{
	return this->CargosOutputLines;
}

bool Company::ForceMoveMaintenanceToAvailable(TRUCKTYPE type) {

	Truck* pTruck;

	switch (type)
	{
	case TRUCKTYPE::NT:
		if (this->NormalMaintenanceTrucksList->getCount() == 0) return false;
		this->NormalMaintenanceTrucksList->dequeue(pTruck);
		pTruck->SetSpeed(pTruck->GetSpeed() / 2);
		this->NormalTrucksList->enqueue(pTruck);
		return true;
		break;
	case TRUCKTYPE::ST:
		if (this->SpecialMaintenanceTrucksList->getCount() == 0) return false;
		this->SpecialMaintenanceTrucksList->dequeue(pTruck);
		pTruck->SetSpeed(pTruck->GetSpeed() / 2);
		this->SpecialTrucksList->enqueue(pTruck);
		return true;
		break;
	case TRUCKTYPE::VT:
		if (this->VIPMaintenanceTrucksList->getCount() == 0) return false;
		this->VIPMaintenanceTrucksList->dequeue(pTruck);
		pTruck->SetSpeed(pTruck->GetSpeed() / 2);
		this->VIPTrucksList->enqueue(pTruck);
		return true;
		break;
	}
	return false;
}


#endif	