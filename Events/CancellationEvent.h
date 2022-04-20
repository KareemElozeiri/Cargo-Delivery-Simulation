#pragma once
#include "Event.h"
#include "../Company.h"

class CancellationEvent: public Event
{
public:
	CancellationEvent(Company* AppMngr, Time* EventTime, int ID) : Event(AppMngr, EventTime, ID) {};
	virtual void Execute();
};

