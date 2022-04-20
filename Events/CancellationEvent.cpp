#include "CancellationEvent.h"

void CancellationEvent::Execute() {
	AppMngr->DeleteNormalCargo(ID);
}