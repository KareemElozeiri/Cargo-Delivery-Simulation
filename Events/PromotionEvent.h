#ifndef PROMOTION_EVENT_H
#define PROMOTION_EVENT_H

#include "Event.h"
class PromotionEvent: public Event
{
private:
	double ExtraMoney; // Extra money for promotion

public:
	virtual void Execute();
};

#endif