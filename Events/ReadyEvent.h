#pragma once
#include "Event.h"
#include "../Defs.h"
#include "../Company.h"

class ReadyEvent: public Event
{
private:
	CARGOTYPE CType; // Cargo type
	int Distance; // Cargo distance in kilometers
	Time* LT; // Time in hours to load or unload the cargo
	int Cost; // Cargo cost

public:
	ReadyEvent(Company* AppMngr, Time* EventTime, int ID, CARGOTYPE CType, int Distance, Time* LT, int Cost) : Event(AppMngr, EventTime, ID), 
		CType(CType), Distance(Distance), LT(LT), Cost(Cost) {};
	virtual void Execute();
};

