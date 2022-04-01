#pragma once
#include "../DataStructures/Date.h"

class Cargo {
protected:
	int CargoID;
	Date preparation_time;
	int load_time;
	double delivery_distance;
	double cost;
	
public:
	virtual Date getPrepTime() = 0;
	virtual int getLoadTime() = 0;
	virtual double getDeliveryDistance() = 0;
	virtual double getCost() = 0;
	virtual int getID() = 0;

};
