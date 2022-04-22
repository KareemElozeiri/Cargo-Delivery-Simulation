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
}

Company::~Company() {
	this->SaveOutputs();
}

bool Company::CheckExitStatus() {
	// check for application status 
	// The simulation function stops when there are no more events and all cargos are in delivered list

	return (this->NormalCargoList->isEmpty() && this->SpecialCargoList->isEmpty() && this->VIPCargoList->isEmpty() && this->EventList->isEmpty());
}

void Company::Simulate() {
	while (true) {
		this->TimestepNum = this->TimestepNum + 1;

		// Execute the upcoming event
		this->ExecuteUpcomingEvent();

	
		if (this->TimestepNum.GetTotalHours() % 5 == 0) {
			//move cargo
			Cargo* nc = nullptr; 
			Cargo* sc = nullptr;
			Cargo* vc = nullptr;

			if(this->NormalCargoList->GetHead()) nc = this->NormalCargoList->GetHead()->getItem();
		    this->SpecialCargoList->dequeue(sc);
		    this->VIPCargoList->dequeue(vc);

			if (nc != nullptr) 
			{
				this->DeliveredNormalCargoList->enqueue(nc);
				this->DeleteNormalCargo(nc->GetID());
			}

			if (sc != nullptr) this->DeliveredSpecialCargoList->enqueue(sc);
			if (vc != nullptr) this->DeliveredVIPCargoList->enqueue(vc);
		}

		// print current info
		this->UpdateInterface();
			

		//check break conditions
		if (this->CheckExitStatus())
		{
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
	Time* EventTime = splitTime(sEventTime);

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

	Time* EventTime = splitTime(sEventTime);

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
	
	Time* EventTime = splitTime(sEventTime);
	
	int ID;
	inputFile >> ID;
	float ExtraMoney;
	inputFile >> ExtraMoney;
	Event* pEvent = new PromotionEvent(this, EventTime, ID, ExtraMoney);
	this->AddEvent(pEvent);
}




/// There was AddEvents function here and I replaced it with ReadEvents
/// purpose: to read from files and then call the Event class
/// if it has different purpose, add it again 


void Company::SaveOutputs() {
	// called on exit
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
        pUI->StepInterfaceUpdate();
        break;
    case MODE::SILENT:
        pUI->SilentInterfaceUpdate();
        break;
    }
}

std::string Company::GetInteractiveModeData() const {
	string interactive_mode_data;
	string separator = "\n--------------------------------------------------\n";

	int WaitingCargosCount, LoadingTrucksCount, EmptyTrucksCount, MovingCargosCout,
		InCheckupTrucksCount, DeliveredCargosCount;

	WaitingCargosCount = this->NormalCargoList->getCount() + 
		this->SpecialCargoList->getCount() +
		this->VIPCargoList->getCount();

	LoadingTrucksCount = this->NormalTrucksList->getCount() +
		this->SpecialTrucksList->getCount() +
		this->VIPTrucksList->getCount();

	DeliveredCargosCount = this->DeliveredNormalCargoList->getCount() +
		this->DeliveredSpecialCargoList->getCount() +
		this->DeliveredVIPCargoList->getCount();


	// Waiting Cargos Line:
	interactive_mode_data += WaitingCargosCount + " Waiting Cargos: ";
	interactive_mode_data += "[" + this->NormalCargoList->getData() + "] ";
	interactive_mode_data += "(" + this->SpecialCargoList->getData() + ") ";
	interactive_mode_data += "{" + this->VIPCargoList->getData() + "}";
	interactive_mode_data += separator;
	
	interactive_mode_data += DeliveredCargosCount + " Delivered Cargos: ";
	interactive_mode_data += "[" + this->DeliveredNormalCargoList->getData() + "] ";
	interactive_mode_data += "(" + this->DeliveredSpecialCargoList->getData() + ") ";
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

	double priority_calc = pCargo->GetCost() / 2000
		- pCargo->GetDeliveryDistance() / 2000
		- pCargo->GetPrepTime()->GetTotalHours() / 5
		- pCargo->GetLoadTime() / 10;


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

#endif 