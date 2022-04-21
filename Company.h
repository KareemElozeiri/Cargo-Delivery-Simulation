#ifndef  Company_H
#define Company_H


#include "Defs.h"
#include "DataStructures/PQueue.h"
#include "DataStructures/LinkedList.h"
#include "Events/Event.h"
#include "Events/CancellationEvent.h"
#include "Events/PromotionEvent.h"
#include "Events/ReadyEvent.h"
#include "SimulationAgents/Cargo.h"
#include "SimulationAgents/Truck.h"
#include "SimulationAgents/Time.h"
#include "UI/UI.h"
#include "custom/customs.h" //to get split function
#include <iostream>
#include <fstream>

class Company
{

private:
	int TimestepNum; // increment on each step (check on 5 and reset)

	UI* pUI; // UI object

	Queue<Event*>* EventList = new Queue<Event*>; 
	LinkedList<Cargo*>* NormalCargoList = new LinkedList<Cargo*>; // move cargo if found (using id of cargo) 
	Queue<Cargo*>* SpecialCargoList = new Queue<Cargo*>;
	PQueue<Cargo*>* VIPCargoList = new PQueue<Cargo*>; //
	Queue<Cargo*>* CargoWaitList = new Queue<Cargo*>;
	//// Trucks queues
	Queue<Truck*>* NormalTrucksList = new Queue<Truck*>;
	Queue<Truck*>* SpecialTrucksList = new Queue<Truck*>;
	Queue<Truck*>* VIPTrucksList = new Queue<Truck*>;

	Time AutoPromotionLimit; // supposed to read days from the input file
	Time MaxWaitingTime;	 // the maximum time that a truck should wait before loading cargo || supposed to read hours from the input file

	string inputFileName = "Loads/input.txt";
	int NumOfEvents;

public:
	Company();
	~Company();

	bool CheckExitStatus(); // returns if the program is finished or not (stops the main loop)
	void Simulate();	// timestep made by the main loop
	void UpdateInterface(); // based on the selected display type

	void LoadInputs(); // executes the load class to load all the info into the lists
	void SaveOutputs(); // saves output on exit
	

	void AddTruck(TRUCKTYPE truck_type, int capacity, Time checkUpTime, int journeysBeforeCheckUp, double speed); // adds a truck to the truck list
	void AddEvent(Event* pEvent); // adds new event to the events list
	void AddWaitCargo(Cargo* pCargo);
	
	void ReadReadyEvent(std::ifstream& inputFile);// adds read event to the event queue 
	void ReadPromotionEvent(std::ifstream& inputFile);		// adds promotion event to the event queue
	void ReadCancellationEvent(std::ifstream& inputFile);	// adds cargo cancellation to the event queue 

	Cargo* FindNormalCargo(int ID);
	void DeleteNormalCargo(int ID);
	void AddVIPCargo(Cargo* pCargo);
};
#endif