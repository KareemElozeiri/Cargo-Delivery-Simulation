#include "PromotionEvent.h"

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
