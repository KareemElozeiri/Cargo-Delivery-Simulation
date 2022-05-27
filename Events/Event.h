#ifndef EVENT_H
#define EVENT_H

#include "../SimulationAgents/Time.h"

class Company; // Forward class declaration

class Event 
{
protected:
	Company* AppMngr;
	Time EventTime;
	int ID;

public:
	
	/*
	* Function: Event.
	* The Event Constructor.
	*
	* Parameters:
	*	- AppMngr : Pointer to the Company instance (App Manager).
	*	- EventTime : The Time at which the event should be executed.
	*	- ID : The ID of the object the event will act upon.
	*
	* Returns: void.
	*/
	Event(Company* AppMngr, Time EventTime, int ID) : AppMngr(AppMngr), EventTime(EventTime), ID(ID) {}

	/*
	* Function: Execute.
	* Executes the inherited event.
	*
	* Returns: void.
	*/
	virtual void Execute() = 0;

	/*
	* Function: GetEventTime.
	* Returns the time at which the event should be executed.
	*
	* Returns: Time.
	*/
	Time GetEventTime() const { return EventTime; }

	/*
	* Function: GetEventID.
	* Returns the ID of the object the event will act upon.
	*
	* Returns: int.
	*/
	int GetEventID() const { return ID; }
};

#endif