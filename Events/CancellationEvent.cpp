#ifndef CANCELLATION_EVENT_CPP
#define CANCELLATION_EVENT_CPP

#include "CancellationEvent.h"

void CancellationEvent::Execute() {

	if (!AppMngr->isChangeableCargo(ID)) {
		return;
	}

	Cargo* pCargo = nullptr;
	pCargo = AppMngr->FindNormalCargo(ID);
	AppMngr->DeleteNormalCargo(ID);
	delete pCargo;
}

#endif