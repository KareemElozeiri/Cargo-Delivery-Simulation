#ifndef CANCELLATION_EVENT_CPP
#define CANCELLATION_EVENT_CPP

#include "CancellationEvent.h"

void CancellationEvent::Execute() {
	Cargo* pCargo = nullptr;
	pCargo = AppMngr->FindNormalCargo(ID);
	if (pCargo != nullptr) {
		AppMngr->DeleteNormalCargo(ID);
	}
}

#endif