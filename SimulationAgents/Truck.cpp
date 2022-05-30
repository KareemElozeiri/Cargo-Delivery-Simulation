#ifndef TRUCK_CPP
#define TRUCK_CPP

#include "Truck.h"

Truck::Truck() {}

Truck::Truck(TRUCKTYPE truck_type, int capacity, Time checkUpTime, int journeysBeforeCheckUp, double speed, int id)
{
	this->truck_type = truck_type;
	this->capacity = capacity;
	this->checkUpTime = checkUpTime;
	this->speed = speed;
	this->journeysBeforeCheckUp = journeysBeforeCheckUp;
	this->maxjourneysBeforeCheckUp = journeysBeforeCheckUp;
	this->ID = id;
	this->CalculateDeliveryInterval();
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
	return this->journeysBeforeCheckUp;
}

void Truck::CalculateDeliveryInterval()
{

	this->deliveryInterval = 2* (this->max_distance_to_deliver/this->speed);
}

int Truck::GetID() const
{
	return this->ID;
}

void Truck::SetID(int id)
{
	this->ID = id;
}



bool Truck::LoadCargo(Cargo* cargo)
{
	if (cargo != nullptr) {
		if (this->cargos->getCount() <this->capacity) {
			//adding load time of the cargo to the total time spent
			//by the truck waiting for the cargos to be loaded
			this->total_load_time = this->total_load_time + cargo->GetLoadTime();
			//setting max distance that the truck will move to 
			if (cargo->GetDeliveryDistance() > this->max_distance_to_deliver)
				this->max_distance_to_deliver = cargo->GetDeliveryDistance();
			//checking minimumm time required for delivering a cargo

			double cargo_priority = -(cargo->GetDeliveryDistance() / this->speed + cargo->GetLoadTime());
			this->cargos->enqueue(cargo, cargo_priority);
			this->CalculateDeliveryInterval();
			this->UpdateTruckPriority();

			if (this->cargos->getCount() == this->capacity) {
				this->SetLoaded(true);
				this->SetLoading(false);
			}

			return true;

		}
	}
	return false;

}

void Truck::UpdateTruckPriority() {
	Cargo* TempCargo;
	this->cargos->peek(TempCargo);

	if (TempCargo) {
		this->truck_priority = -(TempCargo->GetDeliveryDistance() / this->speed + TempCargo->GetLoadTime());
	}
}


Time Truck::GetMinimumDeliveryTime() const
{
	Cargo* c;
	this->cargos->peek(c);
	Time t = 0;
	if (c != nullptr) {
		t = c->GetDeliveryDistance()/this->speed;
	}
	
	return t;
}


double Truck::GetTruckPriority() const {
	return this->truck_priority;
}


void Truck::ResetJourneysCount() {
	this->journeysBeforeCheckUp = this->maxjourneysBeforeCheckUp;
}

void Truck::DecreaseJourneyBeforeCheckUp() {
	this->journeysBeforeCheckUp -= 1;
}

int Truck::GetTotalCompletedJourneys() {
	return this->journeysCompleted;
}

int Truck::GetMaxJourneysBeforeCheckUp() {
	return this->maxjourneysBeforeCheckUp;
}

bool Truck::IsLoaded() const
{
	return this->Loaded;
}

void Truck::SetLoaded(bool value)
{
	this->Loaded = value;
}

bool Truck::IsLoading() const
{
	return this->Loading;
}

void Truck::SetLoading(bool loading)
{
	this->Loading = loading;
}

Time Truck::getCheckUpOutTime() const {
	return this->CheckUpOutTime;
}

void Truck::setCheckUpOutTime(Time time) {
	this->CheckUpOutTime = time;
}

CARGOTYPE Truck::GetCargoType() const
{
	return this->cargo_type;
}

void Truck::SetCargoType(CARGOTYPE type)
{
	this->cargo_type = type;
}

std::ostream& operator<<(std::ostream& os , const Truck* truck)
{
	os << truck->GetID();
	return os;
}

std::ostream& operator<<(std::ostream& os, const Truck truck) 
{
	os << truck.GetID();
	return os;
}

void Truck::SetMovingStartTime(Time MovingStartTime) {
	this->MovingStartTime = MovingStartTime;
}

Time Truck::GetMovingStartTime() {
	return this->MovingStartTime;
}

int Truck::GetCargosCount() {
	return this->cargos->getCount();
}

std::string Truck::GetCargosData() {
	return this->cargos->getData();
}

void Truck::PeekCargos(Cargo*& toPeekCargo) {
	this->cargos->peek(toPeekCargo);
}

void Truck::DequeueTopCargo(Cargo*& toDequeueCargo) {
	this->cargos->dequeue(toDequeueCargo);
}

bool Truck::DequeueTopCargo_bool(Cargo*& toDequeueCargo) {
	return this->cargos->dequeue(toDequeueCargo);
}

void Truck::IncrementJourneysCompleted() {
	this->journeysCompleted += 1;
}

#endif