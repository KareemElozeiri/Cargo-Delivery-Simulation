#ifndef CARGO_CPP
#define CARGO_CPP

#include "Cargo.h"

Cargo::Cargo(CARGOTYPE type)
{
	this->Cargo_type = type;
}

Cargo::Cargo(CARGOTYPE type, int cargoID, Time* preparation_time, int load_time, double delivery_distance, double cost)
{
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

void Cargo::SetPrepTime(Time* prep_time) {
	this->preparation_time = prep_time;
}

void Cargo::SetLoadTime(int load_time) {
	this->load_time = load_time;
}

void Cargo::SetDeliveryDistance(double delivery_distance) {
	this->delivery_distance = delivery_distance;
}

void Cargo::SetCost(double cost) {
	this->cost = cost;
}
void Cargo::SetID(int id) {
	this->cargoID = id;
}

// Overloading the cout operator for the cargo

std::ostream& operator<<(std::ostream& os, const Cargo* cargo)
{
	os << cargo->GetID();
	return os;
}

std::ostream& operator<<(std::ostream& os, const Cargo cargo)
{
	os << cargo.GetID();
	return os;
}

#endif