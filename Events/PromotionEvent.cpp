#include "PromotionEvent.h"

PromotionEvent::PromotionEvent(Time ED, int ID_normal_cargo, float ExtraMoney)
{
	this->ED = ED;
	this->ID_normal_cargo = ID_normal_cargo;
	this->ExtraMoney = ExtraMoney;

}

void PromotionEvent::Execute()
{
}
