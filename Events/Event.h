#pragma once
#include "../DataStructures/Date.h"

class Event {
protected:
	Date event_time;
	int ID;

public:
	virtual void Excute() = 0;
	virtual Date event_time() =0;




};
