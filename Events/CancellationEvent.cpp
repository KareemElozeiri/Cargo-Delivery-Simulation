#ifndef CANCELLATION_EVENT_CPP
#define CANCELLATION_EVENT_CPP

#include "CancellationEvent.h"

void CancellationEvent::Execute() {

	if (!AppMngr->isChangeableCargo(ID)) {
		return;
	}

	AppMngr->DeleteNormalCargo(ID);
}

#endif