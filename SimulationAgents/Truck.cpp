#include "Truck.h"

Truck::Truck(int capacity, Time checkUpTime, double speed){
	this->Capacity = capacity;
	this->CheckUpTime = checkUpTime;
	this->Speed = speed;
}

Time Truck::getCheckUpTime() const
{
	return this->CheckUpTime;
}

int Truck::getCapacity() const
{
	return this->Capacity;
}

double Truck::getSpeed() const
{
	return this->Speed;
}

Time Truck::getDeliveryInterval() const
{
	return this->DeliveryInterval;
}

void Truck::CalculateDeliveryInterval()
{
	//still subject to change 
	// we need to connect it to the cargo that it is carrying 
	// find the furthest cargo that it is carrying and perform the equation on it
}
