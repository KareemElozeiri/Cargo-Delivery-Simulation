#pragma once
#include "Event.h"
class PromotionEvent: public Event
{
private:
	double ExtraMoney; // Extra money for promotion

public:
	virtual void Execute();
};

