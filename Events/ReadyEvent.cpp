#ifndef READY_EVENT_CPP
#define READY_EVENT_CPP

#include "ReadyEvent.h"
#include "../SimulationAgents/Cargo.h"

void ReadyEvent::Execute() {
	Cargo* pCargo = new Cargo(CType, ID, EventTime, LT, Distance, Cost);
	AppMngr->AddWaitCargo(pCargo);
}

#endif