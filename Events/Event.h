#pragma once
#include "../Defs.h"

class Event {
protected:
	Time event_time;
	int ID;

public:
	virtual void Excute() = 0;
	//virtual Time event_time() = 0;
};
