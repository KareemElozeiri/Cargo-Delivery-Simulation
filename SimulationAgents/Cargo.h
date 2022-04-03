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
	//getters
	Date getPrepTime();
	int getLoadTime();
	double getDeliveryDistance();
	double getCost();
	int getID();



	//setters
	void setPrepTime(Date p);
	void setLoadTime(int p);
	void setDeliveryDistance(double p);
	void setCost(double p);
	void setID(int p);

};
