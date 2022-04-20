#pragma once
#include "Time.h"
#include "../Defs.h"

class Cargo {
protected:
	CARGOTYPE Cargo_type;
	int cargoID;
	Time* preparation_time;
	int load_time;
	double delivery_distance;
	double cost;
	

public:

	//////Constructor taking all params
	Cargo(CARGOTYPE type);

	//////Constructor taking all params
	Cargo(CARGOTYPE type, int cargoID, Time* preparation_time, int load_time,
		double delivery_distance, double cost);

	//getters
	Time* GetPrepTime() const;
	int GetLoadTime() const;
	double GetDeliveryDistance() const;
	double GetCost() const;
	int GetID() const;
	CARGOTYPE GetType() const;

	//setters
	void SetPrepTime(Time* p);
	void SetLoadTime(int p);
	void SetDeliveryDistance(double p);
	void SetCost(double p);
	void SetID(int p);

};
