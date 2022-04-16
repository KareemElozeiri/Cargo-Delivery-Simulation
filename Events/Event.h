#pragma once
#include "../SimulationAgents/Time.h"

class Event {
protected:
	Time EventTime;
	int ID;

public:
	virtual void Execute() = 0;
};
