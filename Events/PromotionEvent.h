#ifndef PROMOTION_EVENT_H
#define PROMOTION_EVENT_H

#include "Event.h"
#include "../Company.h"

class PromotionEvent: public Event
{
private:
	double ExtraMoney; // Extra money for promotion

public:
	PromotionEvent(Company* AppMngr, Time* EventTime, int ID, double ExtraMoney) : Event(AppMngr, EventTime, ID), ExtraMoney(ExtraMoney) {};
	virtual void Execute();
};

#endif