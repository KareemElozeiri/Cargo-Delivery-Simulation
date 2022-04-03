#include "Cargo.h"

//getters

Date Cargo::getPrepTime()
{
	return preparation_time;
}

int Cargo::getLoadTime()
{
	return load_time;
}

double Cargo::getDeliveryDistance()
{
	return delivery_distance;
}

double Cargo::getCost()
{
	return cost;
}

int Cargo::getID()
{
	return CargoID;
}

//setters

void Cargo::setPrepTime(Date p) {
	preparation_time = p;
}

void Cargo::setLoadTime(int p) {
	load_time = p;
}

void Cargo::setDeliveryDistance(double p) {
	delivery_distance = p;
}

void Cargo::setCost(double p) {
	cost = p;
}
void Cargo::setID(int p) {
	CargoID = p;
}
