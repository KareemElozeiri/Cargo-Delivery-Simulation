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
	Time TimestepNum; // increment on each step (check on 5 and reset)

	UI* pUI; // UI object

	Queue<Event*>* EventList = new Queue<Event*>;
	//waiting lists
	LinkedList<Cargo*>* NormalCargoList = new LinkedList<Cargo*>; // move cargo if found (using id of cargo) 
	Queue<Cargo*>* SpecialCargoList = new Queue<Cargo*>;
	PQueue<Cargo*>* VIPCargoList = new PQueue<Cargo*>;
	// lists to store delivered cargo 
	Queue<Cargo*>* DeliveredNormalCargoList = new Queue<Cargo*>;
	Queue<Cargo*>* DeliveredSpecialCargoList = new Queue<Cargo*>;
	Queue<Cargo*>* DeliveredVIPCargoList = new Queue<Cargo*>;
	//// Trucks queues
	Queue<Truck*>* NormalTrucksList = new Queue<Truck*>;
	Queue<Truck*>* SpecialTrucksList = new Queue<Truck*>;
	Queue<Truck*>* VIPTrucksList = new Queue<Truck*>;
	PQueue<Truck*>* InCheckUpTrucksList = new PQueue<Truck*>;

	Queue<Truck*>* NormalMaintenanceTrucksList = new Queue<Truck*>;
	Queue<Truck*>* SpecialMaintenanceTrucksList = new Queue<Truck*>;
	Queue<Truck*>* VIPMaintenanceTrucksList = new Queue<Truck*>;

	PQueue<Truck*>* MovingTrucks = new PQueue<Truck*>;

	Time AutoPromotionLimit; // supposed to read days from the input file
	Time MaxWaitingTime;	 // the maximum time that a truck should wait before loading cargo || supposed to read hours from the input file

	string inputFileName;
	string outputFileName;
	int NumOfEvents;

	/*
	* takes a given queue whose inner values are pointers
	* delete these inner pointers one by one
	*/

	template <typename T>
	void cleanQueueInnerPointers(Queue<T*>* queue);

	/*
	* takes a given priority queue whose inner values are pointers
	* delete these inner pointers one by one
	*/
	template <typename T>
	void cleanPriorityQueueInnerPointers(PQueue<T*>* pqueue);


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
	* Function: SaveOutputs.
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
	void AddTruck(TRUCKTYPE truck_type, int capacity, Time checkUpTime, int journeysBeforeCheckUp,double speed, int id);
	
	/*
	* Function: MoveTrucks.
	* Moves the upcoming trucks to the moving trucks list if applicable.
	*
	* Parameters:
	*	NO PARAMS.
	*/
	void MoveTrucks();

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

	/*
	* Function: ExecuteUpcomingEvent.
	* Executes the upcoming event if its time has come.
	*/
	bool ExecuteUpcomingEvent();

	/*
	* Function: GetInteractiveModeData.
	* Returns the interactive mode data to be printed on the CLI.
	*
	* Returns: string.
	*/
	std::string GetInteractiveModeData() const;

	/*
	* Function: GetCurrentTime.
	* Returns the current time step.
	*
	* Returns: string.
	*/
	std::string GetCurrentTime();

	/* 
	* Function: LoadVIPCargosToTruck
	* Handles the logic for loading VIP cargos to the proper truck
	* Returns: true if the loading went successfully
	* Returns: false if the loading failed
	*/
	bool LoadVIPCargosToTruck();

	/*
	* Function: LoadVIPCargosToTruck
	* Handles the logic for loading special cargos to the proper truck
	* Returns: true if the loading went successfully
	* Returns: false if the loading failed
	*/
	bool LoadSpecialCargosToTruck();

	/*
	* Function: LoadVIPCargosToTruck
	* Handles the logic for loading Normal cargos to the proper truck
	* Returns: true if the loading went successfully
	* Returns: false if the loading failed
	*/
	bool LoadNormalCargosToTruck();

	/*
	* Function: LoadTruck
	* Takes the truck to be loaded and the queue that it should load from
	*/
	void LoadTruck(Truck* truck, Queue<Cargo*>* cargoQueue);

	/*
	* Overloads the previos function to handle Cargo list 
	* whose data structure type is linked list
	*/
	void LoadTruck(Truck*, LinkedList<Cargo*>* cargoList);

	/*
	* checks if a truck can load
	*/
	bool CanTruckLoad(Truck* truck, Queue<Cargo*>* givenQueue);
	bool CanTruckLoad(Truck* truck, LinkedList<Cargo*>* givenList);


	bool OtherTwoNotWorkingOnThat(Truck* truck1, Truck* truck2, CARGOTYPE c);

	/*
	*Checks if cargo is allowed to be promoted or canceled
	*/
	bool isChangeableCargo(int ID);

	void AutoPromote(Cargo* pCargo);
	void checkForAutoPromote();

	/*
	* Function: CheckMaxWaitingTime
	* Checks if a given cargo has waited for the maximum waiting time
	*/
	bool CheckMaxWaitingTime(Cargo* c);
	void CheckForCheckUp();
	void MoveCheckUpToAvailable();
	bool CheckForMaintenance(Truck* pTruck);
	void MoveMaintenanceToAvailable();




	// TODO
	TRUCKTYPE CheckTrucksNeeded(); // get what truck type needed
	void ForceMoveMaintenanceToAvailable(TRUCKTYPE type); // release one of the trucks in the list
};
#endif

