#include "Cargo.h"

//getters

Time Cargo::GetPrepTime()
{
	return this->preparation_time;
}

Time Cargo::GetLoadTime()
{
	return this->load_time;
}

double Cargo::GetDeliveryDistance()
{
	return this->delivery_distance;
}

double Cargo::GetCost()
{
	return this->cost;
}

int Cargo::GetID()
{
	return this->cargoID;
}

//setters

void Cargo::SetPrepTime(Time p) {
	this->preparation_time = p;
}

void Cargo::SetLoadTime(Time p) {
	this->load_time = p;
}

void Cargo::SetDeliveryDistance(double p) {
	this->delivery_distance = p;
}

void Cargo::SetCost(double p) {
	this->cost = p;
}
void Cargo::SetID(int p) {
	this->cargoID = p;
}
