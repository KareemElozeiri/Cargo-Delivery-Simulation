#ifndef READY_EVENT_H
#define READY_EVENT_H

#include "Event.h"
#include "../Defs.h"
#include "../Company.h"

class ReadyEvent: public Event
{
private:
	CARGOTYPE CType; // Cargo type
	int Distance; // Cargo travel distance in kilometers
	int LT; // Time in hours to load or unload the Cargo
	int Cost; // Cargo cost

public:

	/*
	* Function: ReadyEvent.
	* The ReadyEvent Constructor.
	*
	* Parameters:
	*	- AppMngr : Pointer to the Company instance (App Manager).
	*	- EventTime : The Time at which the event should be executed.
	*	- ID : The ID of the object that will get cancelled.
	*	- CType : The Cargo's type.
	*	- Distance : The distance the Cargo should travel in km.
	*	- LT : Time in hours to load/unload the Cargo.
	*	- Cost : The Cargo's cost.
	*
	* Returns: void.
	*/
	ReadyEvent(Company* AppMngr, Time EventTime, int ID, CARGOTYPE CType, int Distance, int LT, int Cost) : Event(AppMngr, EventTime, ID), 
		CType(CType), Distance(Distance), LT(LT), Cost(Cost) {};

	/*
	* Function: Execute.
	* Executes the Ready event.
	*
	* Returns: void.
	*/
	virtual void Execute();
};

#endif