#ifndef PROMOTION_EVENT_H
#define PROMOTION_EVENT_H

#include "Event.h"
#include "../Company.h"

class PromotionEvent: public Event
{
private:
	double ExtraMoney; // Extra-money for promotion

public:

	/*
	* Function: PromotionEvent.
	* The PromotionEvent Constructor.
	*
	* Parameters:
	*	- AppMngr : Pointer to the Company instance (App Manager).
	*	- EventTime : The Time at which the event should be executed.
	*	- ID : The ID of the object that will get cancelled.
	*	- ExtraMoney : The extra money that will be added to the promoted cargo.
	*
	* Returns: void.
	*/
	PromotionEvent(Company* AppMngr, Time EventTime, int ID, double ExtraMoney) : Event(AppMngr, EventTime, ID), ExtraMoney(ExtraMoney) {};
	
	/*
	* Function: Execute.
	* Executes the Promotion event.
	*
	* Returns: void.
	*/
	virtual void Execute();
};

#endif