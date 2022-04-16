#include "Cargo.h"

//getters

Cargo::Cargo(CARGOTYPE type)
{
	this->Cargo_type = type;
}

Cargo::Cargo(CARGOTYPE type, int cargoID, Time preparation_time, Time load_time, double delivery_distance, double cost)
{
	////////////////////////////////
	/////////////the cargoID will be automatically generated as per our agreement
	this->Cargo_type = type;
	this->cargoID = cargoID;
	this->preparation_time = preparation_time;
	this->load_time = load_time;
	this->delivery_distance = delivery_distance;
	this->cost = cost;
}



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

CARGOTYPE Cargo::GetType()
{
	return Cargo_type;
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
