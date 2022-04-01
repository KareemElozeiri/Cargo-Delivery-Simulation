#pragma once
#include "Cargo.h"
class CargoTypeTest :public Cargo
{
	Date getPrepTime();
	int getLoadTime();
	double getDeliveryDistance();
	double getCost();
	int getID();


	//void setPrepTime(Date p);
	//void setLoadTime(int p);
	//void setDeliveryDistance(double p);
	//void setCost(double p);
	//void setID(int p);

};
