#ifndef CANCELLATION_EVENT_H
#define CANCELLATION_EVENT_H

#include "Event.h"
#include "../Company.h"

class CancellationEvent: public Event
{
public:

	/*
	* Function: CancellationEvent.
	* The CancellationEvent Constructor.
	*
	* Parameters:
	*	- AppMngr : Pointer to the Company instance (App Manager).
	*	- EventTime : The Time at which the event should be executed.
	*	- ID : The ID of the object that will get cancelled.
	*
	* Returns: void.
	*/
	CancellationEvent(Company* AppMngr, Time* EventTime, int ID) : Event(AppMngr, EventTime, ID) {};

	/*
	* Function: Execute.
	* Executes the cancellation event.
	*
	* Returns: void.
	*/
	virtual void Execute();
};

#endif