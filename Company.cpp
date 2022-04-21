#include "Company.h"

#include "Events/CancellationEvent.h"
#include "Events/PromotionEvent.h"
#include "Events/ReadyEvent.h"



Company::Company() {
	this->TimestepNum = 0;

	this->pUI = new UI;

	// initialize load function
	this->LoadInputs();
}

Company::~Company() {
	this->SaveOutputs();
}

bool Company::CheckExitStatus() {
	// check for application status 
	// The simulation function stops when there are no more events and all cargos are in delivered list
	return false;
}

void Company::Simulate() {
	/*Simple Simulator function for Phase 1. 
	The main purpose of this function is to test different 
	lists and make sure all operations on them are working properly. 
	This function should: Perform any needed initializations
	Call file loading function
	At each timestep do the following:
	Get the events that should be executed at current timestep
	For Preparation event,
	generate a cargo and add it to the appropriate waiting cargos list.
	For cancellation event, delete the corresponding normal cargo (if found)
	For promotion event, move cargo (if found) from normal to VIP.
	Each 5 timesteps, move a cargo of each type from waiting-cargo list(s) to delivered list(s) 
	(The cargo you choose to delete from each type must be the first cargo that should be assigned to an available truck in phase 2.)
	Print all applicable info to the interface as described in �Program Interface� section without truck info.
	Notes:The simulation function stops when there are no more events and all cargos are in delivered list(s)*/

	this->TimestepNum += 1;

	// Check Eventlist for any occuring ones

	if (this->TimestepNum == 5) {
		this->TimestepNum = 0;
		// 4-b waiting cargo list operation
	}
}

void Company::LoadInputs() {
	using std::ifstream;
	ifstream inputFile(this->inputFileName);

	//checking that the stream open successfully 
	if (!inputFile.is_open()) {
		//this->pUI->PrintMsg("*** Error: Could not open " + this->inputFileName + " ***");
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

	//reading events from the file
	
	/// loops on each event and takes the letter to check which event function to call.
	/// based on this the event function will take the right number of params for it
	/// Ready : 6 params
	/// Cancellation: 2 params
	/// Promotional: 3 params
	
	inputFile >> NumOfEvents;

	for (int i = 0; i < NumOfEvents; i++) {
		char EventChar;
		inputFile >> EventChar;

		if (EventChar == 'R')
			ReadReadyEvent(inputFile);
		else if (EventChar == 'P')
			ReadPromotionEvent(inputFile);
		else if (EventChar == 'C')
			ReadCancellationEvent(inputFile);
	}


	//adding VIP trucks
	for (int i = 0; i < vTrucksNum; i++)
		this->AddTruck(VT, vCapacity, Time(vCheckUpHours), JourNum, vTruckSpeed);

	//adding special trucks
	for (int i = 0; i < sTrucksNum; i++)
		this->AddTruck(ST, sCapacity, Time(sCheckUpHours), JourNum, sTruckSpeed);

	//adding normal trucks
	for (int i = 0; i < sTrucksNum; i++)
		this->AddTruck(NT, nCapacity, Time(nCheckUpHours), JourNum, nTruckSpeed);

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
	string TimeList[2];
	//////////////has to make a function to split the time and save it in time_list ex: 5:11 ---> ["5","11"]
	Time* EventTime = new Time(stoi(TimeList[0]), stoi(TimeList[1]));
	
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
	//////////////has to make a function to split the time and save it in time_list ex: 5:11 ---> ["5","11"]
	Time* EventTime = new Time(stoi(TimeList[0]), stoi(TimeList[1]));

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
	//////////////has to make a function to split the time and save it in time_list ex: 5:11 ---> ["5","11"]
	Time* EventTime = new Time(stoi(TimeList[0]), stoi(TimeList[1]));
	
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

void Company::AddTruck(TRUCKTYPE truck_type, int capacity, Time checkUpTime, int journeysBeforeCheckUp, double speed)
{
	Truck* truck = new Truck(truck_type, capacity, checkUpTime, journeysBeforeCheckUp, speed);
	this->TruckList->enqueue(truck);
}

void Company::UpdateInterface() {
	//pUI->Step(this);
}

void Company::AddEvent(Event* pEvent) {
	this->EventList->enqueue(pEvent);
}

void Company::AddWaitCargo(Cargo* pCargo) {
	this->CargoWaitList->enqueue(pCargo);
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
	Node<Cargo*>* Head = this->NormalCargoList->GetHead();
	Node<Cargo*>* Prev = nullptr;

	while (Head != nullptr) {
		if (Head->getItem()->GetID() == ID) {
			if (this->NormalCargoList->GetHead() == Head) {
				this->NormalCargoList->SetHead(Head->getNext());
			}
			else {
				Prev->setNext(Head->getNext());
			}
			delete Head->getItem();
			delete Head;
			break;
		}
		Prev = Head;
		Head = Head->getNext();
	}
	
}

/*
	- Priority doesn't only depend on the cost. *Need to change*
*/
void Company::AddVIPCargo(Cargo* pCargo) {
	this->VIPCargoList->enqueue(pCargo, pCargo->GetCost());
}