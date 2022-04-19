#include "Company.h"


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
	Print all applicable info to the interface as described in “Program Interface” section without truck info.
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
		this->AddTruck(VT, vCapacity, Time(vCheckUpHours), JourNum, vTruckSpeed);

	//adding special trucks
	for (int i = 0; i < sTrucksNum; i++)
		this->AddTruck(ST, sCapacity, Time(sCheckUpHours), JourNum, sTruckSpeed);

	//adding normal trucks
	for (int i = 0; i < sTrucksNum; i++)
		this->AddTruck(NT, nCapacity, Time(nCheckUpHours), JourNum, nTruckSpeed);

}

void Company::SaveOutputs() {
	// called on exit
}

void Company::AddReadyEvent()
{
}

void Company::AddPromotionEvent()
{
}

void Company::AddCancellationEvent()
{
}

void Company::AddTruck(TRUCKTYPE truck_type, int capacity, Time checkUpTime, int journeysBeforeCheckUp, double speed)
{
	Truck truck(truck_type, capacity, checkUpTime, journeysBeforeCheckUp, speed);
	this->TruckList->enqueue(truck);
}

void Company::UpdateInterface() {
	//pUI->Step(this);
}

