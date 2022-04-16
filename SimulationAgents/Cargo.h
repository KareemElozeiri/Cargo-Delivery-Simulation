#pragma once
#include "../Defs.h"

class Cargo {
protected:
	int cargoID;
	Time preparation_time;
	Time load_time;
	double delivery_distance;
	double cost;
	
public:
	//getters
	Time GetPrepTime();
	Time GetLoadTime();
	double GetDeliveryDistance();
	double GetCost();
	int GetID();

	//setters
	void SetPrepTime(Time p);
	void SetLoadTime(Time p);
	void SetDeliveryDistance(double p);
	void SetCost(double p);
	void SetID(int p);

};
