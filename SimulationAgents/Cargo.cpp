#include "Cargo.h"

//getters

Cargo::Cargo(CARGOTYPE type)
{
	this->Cargo_type = type;
}

Cargo::Cargo(CARGOTYPE type, int cargoID, Time* preparation_time, int load_time, double delivery_distance, double cost)
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



Time* Cargo::GetPrepTime() const
{
	return this->preparation_time;
}

int Cargo::GetLoadTime() const
{
	return this->load_time;
}

double Cargo::GetDeliveryDistance() const
{
	return this->delivery_distance;
}

double Cargo::GetCost() const
{
	return this->cost;
}

int Cargo::GetID() const
{
	return this->cargoID;
}

CARGOTYPE Cargo::GetType() const
{
	return Cargo_type;
}

//setters

void Cargo::SetPrepTime(Time* p) {
	this->preparation_time = p;
}

void Cargo::SetLoadTime(int p) {
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

// overloading the cout operator for the cargo 
std::ostream& operator<<(std::ostream& os, const Cargo* cargo)
{
	os << cargo->GetID();
}

std::ostream& operator<<(std::ostream& os, const Cargo cargo)
{
	os << cargo.GetID();
}
