#pragma once
#include "../Defs.h"

class Event {
protected:
	Time EventTime;
	int ID;

public:
	virtual void Execute() = 0;
};
