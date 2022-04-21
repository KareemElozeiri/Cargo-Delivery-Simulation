#ifndef EVENT_H
#define EVENT_H

#include "../SimulationAgents/Time.h"

class Company; //forward class declaration

class Event {
protected:
	Company* AppMngr;
	Time* EventTime;
	int ID;

public:
	Event(Company* AppMngr, Time* EventTime, int ID) : AppMngr(AppMngr), EventTime(EventTime), ID(ID){}
	virtual void Execute() = 0;

	Time GetEventTime() const { return *EventTime; }
	int GetEventID() const { return ID; }
};

#endif