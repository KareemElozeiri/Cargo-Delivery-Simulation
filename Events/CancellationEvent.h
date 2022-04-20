#ifndef CANCELLATION_EVENT_H
#define CANCELLATION_EVENT_H

#include "Event.h"
class CancellationEvent: public Event
{
public:
	virtual void Execute();
};

#endif