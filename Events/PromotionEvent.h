#pragma once
#include "Event.h"

class PromotionEvent: public Event
{
private:
	double ExtraMoney; // Extra money for promotion
	Time ED;
	int ID_normal_cargo;


public:

	PromotionEvent(Time ED, int ID_normal_cargo, float ExtraMoney=0);
	virtual void Execute();
};

