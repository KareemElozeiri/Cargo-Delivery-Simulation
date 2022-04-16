#pragma once
#include "Defs.h"
#include "DataStructures/PQueue.h"
#include "Events/Event.h"
#include "SimulationAgents/Cargo.h"
#include "SimulationAgents/Truck.h"
#include "UI/UI.h"

class Company
{

private:
	int TimestepNum; // increment on each step (check on 5 and reset)

	UI* pUI; // UI object

	Queue<Event>* EventList; // Can not create queue of abstract Event type <<<<<<<<<<<<<<<<<<<<<<<<
	Queue<Cargo>* NormalCargoList;
	Queue<Cargo>* SpecialCargoList;
	PQueue<Cargo>* VIPCargoList;
	Queue<Cargo>* CargoWaitList;
	Queue<Truck>* TruckList;

public:
	Company();
	~Company();

	bool CheckExitStatus(); // returns if the program is finished or not (stops the main loop)
	void Simulate();	// timestep made by the main loop
	void UpdateInterface(); // based on the selected display type
	void LoadInputs(); // executes the load class to load all the info into the lists
	void SaveOutputs(); // saves output on exit
};

