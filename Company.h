#pragma once
#include "Defs.h"
#include "DataStructures/PQueue.h"
#include "DataStructures/LinkedList.h"
#include "Events/Event.h"
#include "SimulationAgents/Cargo.h"
#include "SimulationAgents/Truck.h"
#include "UI/UI.h"
#include "SimulationAgents/Time.h"

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
	Queue<Truck*>* TruckList = new Queue<Truck*>;

	string inputFileName = "input.txt";
	int NumOfEvents;

public:

	/*
	* Function: Company.
	* Default Constructor.
	*/
	Company();

	/*
	* Function: Company.
	* Non-Default Constructor.
	*/
	~Company();
	
	/*
	* Function: CheckExitStatus.
	* Checks whether the program should terminate or not (Stops the main loop).
	*/
	bool CheckExitStatus();
	
	/*
	* Function: Simulate.
	* Manages the cargos, trucks, events, time-steps, and simulate the process.
	*/
	void Simulate();
	
	/*
	* Function: UpdateInterface.
	* Based on the current conditions, it updates the interface and calls the required functions.
	*/
	void UpdateInterface();
	
	/*
	* Function: LoadInputs.
	* Loads the inputs info into the lists.
	*/
	void LoadInputs();
	
	/*
	* Function: LoadInputs.
	* Saves the program instance output upon exit.
	*/
	void SaveOutputs();

	/*
	* Function: AddEvent.
	* Adds a new event to the events' list.
	*
	* Parameters:
	*	- pEvent : The event to be added to the list.
	*/
	void AddEvent(Event* pEvent);

	/*
	* Function: AddWaitCargo.
	* Adds a cargo to the waiting cargos' list.
	*
	* Parameters:
	*	- pCargo : The cargo to be added to the list.
	*/
	void AddWaitCargo(Cargo* pCargo);

	/*
	* Function: ReadReadyEvent.
	* Adds a read event to the events queue.
	*/
	void ReadReadyEvent(std::ifstream& inputFile); 
	
	/*
	* Function: ReadPromotionEvent.
	* Adds a promotion event to the events queue.
	*/
	void ReadPromotionEvent(std::ifstream& inputFile);

	/*
	* Function: ReadCancellationEvent.
	* Adds a cancellation event to the events queue.
	*/
	void ReadCancellationEvent(std::ifstream& inputFile);

	/*
	* Function: AddTruck.
	* Adds a new truck to the trucks' list.
	*
	* Parameters:
	*	- truck_type : The type of the truck to be added to the list.
	*	- capacity : The truck's capacity.
	*	- checkUpTime : The checkup time of the truck.
	*	- journeysBeforeCheckUp : The journeys before checkup of the truck.
	*	- speed : The truck's speed.
	*/
	void AddTruck(TRUCKTYPE truck_type, int capacity, Time checkUpTime, int journeysBeforeCheckUp,double speed);
	
	/*
	* Function: FindNormalCargo.
	* Finds a normal cargo by ID.
	*
	* Parameters:
	*	- ID : the cargo's ID.
	*/
	Cargo* FindNormalCargo(int ID);

	/*
	* Function: DeleteNormalCargo.
	* Deletes a normal cargo by ID.
	*
	* Parameters:
	*	- ID : the cargo's ID.
	*/
	void DeleteNormalCargo(int ID);
	
	/*
	* Function: AddVIPCargo.
	* Adds a VIP Cargo to the appropriate list.
	*
	* Parameters:
	*	- pCargo : the cargo to be added.
	*/
	void AddVIPCargo(Cargo* pCargo);
};