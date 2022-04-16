#pragma once
#include "Event.h"
#include "../Defs.h"

class ReadyEvent: public Event
{
private:
	CARGOTYPE CType; // Cargo type
	int Distance; // Cargo distance in kilometers
	int LT; // Time in hours to load or unload the cargo
	int Cost; // Cargo cost

public:
	virtual void Execute();
};

