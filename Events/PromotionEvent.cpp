#ifndef PROMOTION_EVENT_CPP
#define PROMOTION_EVENT_CPP

#include "PromotionEvent.h"

/*
	- Hash map may optimize this.
	- Hash map with an array.
*/

void PromotionEvent::Execute()
{
	Cargo* pCargo = nullptr;
	pCargo = AppMngr->FindNormalCargo(ID);
	if (pCargo != nullptr) {
		AppMngr->DeleteNormalCargo(ID);
		pCargo->SetCost(pCargo->GetCost() + ExtraMoney);
		AppMngr->AddVIPCargo(pCargo);
	}
}

#endif