#include "Truck.h"
/*
Truck::Truck(int capacity, Time checkUpTime, double speed){
	this->capacity = capacity;
	this->checkUpTime = checkUpTime;
	this->speed = speed;
}
*/



Truck::Truck()
{
}

Truck::Truck(TRUCKTYPE truck_type, int capacity, Time checkUpTime, int journeysBeforeCheckUp, double speed)
{
	this->truck_type = truck_type;
	this->capacity = capacity;
	this->checkUpTime = checkUpTime;
	this->speed = speed;
	//this->deliveryInterval = deliveryInterval;
	this->jounrneysBeforeCheckUp = journeysBeforeCheckUp;
}

Time Truck::GetCheckUpTime() const
{
	return this->checkUpTime;
}

TRUCKTYPE Truck::GetTruckType() const
{
	return truck_type;
}

int Truck::GetCapacity() const
{
	return this->capacity;
}

double Truck::GetSpeed() const
{
	return this->speed;
}

Time Truck::GetDeliveryInterval() const
{
	return this->deliveryInterval;
}

int Truck::GetJourneysBeforeCheckUp() const
{
	return this->jounrneysBeforeCheckUp;
}

void Truck::CalculateDeliveryInterval()
{
	//still subject to change 
	// we need to connect it to the cargo that it is carrying 
	// find the furthest cargo that it is carrying and perform the equation on it
}


