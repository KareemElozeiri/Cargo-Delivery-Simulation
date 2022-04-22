#ifndef CANCELLATION_EVENT_CPP
#define CANCELLATION_EVENT_CPP

#include "CancellationEvent.h"
#include <iostream>

void CancellationEvent::Execute() {
	AppMngr->DeleteNormalCargo(ID);
}

#endif