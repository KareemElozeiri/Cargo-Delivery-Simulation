#pragma once
#include "Time.h"
#include "../Defs.h"

class Cargo {
protected:
	CARGOTYPE Cargo_type;
	int cargoID;
	Time preparation_time;
	Time load_time;
	double delivery_distance;
	double cost;
	

public:

	//////Constructor taking all params
	Cargo(CARGOTYPE type);

	//////Constructor taking all params
	Cargo(CARGOTYPE type, int cargoID, Time preparation_time, Time load_time,
		double delivery_distance, double cost);

	//getters
	Time GetPrepTime();
	Time GetLoadTime();
	double GetDeliveryDistance();
	double GetCost();
	int GetID();
	CARGOTYPE GetType();

	//setters
	void SetPrepTime(Time p);
	void SetLoadTime(Time p);
	void SetDeliveryDistance(double p);
	void SetCost(double p);
	void SetID(int p);

};
