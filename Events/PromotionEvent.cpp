#ifndef PROMOTION_EVENT_CPP
#define PROMOTION_EVENT_CPP

#include "PromotionEvent.h"

// Promotes the Normal Cargo to be a VIP one and increases its cost.
void PromotionEvent::Execute()
{
	if (!AppMngr->isChangeableCargo(ID)) {
		return;
	}

	Cargo* pCargo = nullptr;
	pCargo = AppMngr->FindNormalCargo(ID);
	AppMngr->DeleteNormalCargo(ID);
	pCargo->SetCost(pCargo->GetCost() + ExtraMoney);
	AppMngr->AddVIPCargo(pCargo);
}

#endif