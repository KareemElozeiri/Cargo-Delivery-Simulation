#ifndef CARGO_H
#define CARGO_H

#include "Time.h"
#include "../Defs.h"

class Cargo
{
private:
	CARGOTYPE Cargo_type;
	int cargoID;
	Time preparation_time;
	int load_time;
	double delivery_distance;
	double cost;
	Time delivered_time;
	Time Waiting_time;
	int truck_ID;

public:

	Cargo();

	/*
	* Function: Cargo.
	* The Cargo Constructor.
	*
	* Parameters:
	*	- type : The Cargo's type.
	*/
	Cargo(CARGOTYPE type);

	/*
	* Function: Cargo.
	* The Cargo Constructor.
	*
	* Parameters:
	*	- type : The Cargo's type.
	*	- cargoID : The Cargo's id.
	*	- preparation_time : The Cargo's preparation time.
	*	- load_time : The Cargo's loading/unloading time.
	*	- delivery_distance : The Cargo's delivery distance.
	*	- cost : The Cargo's cost.
	*/
	Cargo(CARGOTYPE type, int cargoID, Time preparation_time, int load_time,
		double delivery_distance, double cost);

	/*
	* Function: GetPrepTime.
	* Returns the preparation time of the Cargo.
	*
	* Returns: Time*.
	*/
	Time GetPrepTime() const;
	
	/*
	* Function: GetLoadTime.
	* Returns the loading/unloading time of the Cargo.
	*
	* Returns: int.
	*/
	int GetLoadTime() const;
	
	/*
	* Function: GetDeliveryDistance.
	* Returns the delivery distance of the Cargo.
	*
	* Returns: double.
	*/
	double GetDeliveryDistance() const;


	/*
	* Function: GetDelivereddTime.
	* Gets the time by which a cargo has been delivered.
	*
	* Parameters:
	*	- NO PARAMS
	*
	* Returns: Time.
	*/
	Time GetDeliveredTime();


	/*
	* Function: GetWaitTime.
	* Gets the time the cargo waited until moving
	*
	* Parameters:
	*	- NO PARAMS
	*
	* Returns: Time.
	*/
	Time GetWaitTime();

	/*
	* Function: GetWaitTime.
	* Gets the ID of the truck that moved it.
	*
	* Parameters:
	*	- NO PARAMS
	*
	* Returns: Time.
	*/
	int GetTruckID();
	
	/*
	* Function: GetCost.
	* Returns the cost of the Cargo.
	*
	* Returns: double.
	*/
	double GetCost() const;
	
	/*
	* Function: GetID.
	* Returns the id of the Cargo.
	*
	* Returns: int.
	*/
	int GetID() const;
	
	/*
	* Function: GetType.
	* Returns the type of the Cargo.
	*
	* Returns: CARGOTYPE.
	*/
	CARGOTYPE GetType() const;
	
	/*
	* Function: SetPrepTime.
	* Sets the preparation time of the Cargo.
	*
	* Parameters:
	*	- prep_time : The Preparation time of the Cargo.
	*
	* Returns: void.
	*/
	void SetPrepTime(Time prep_time);
	
	/*
	* Function: SetLoadTime.
	* Sets the loading/unloading time of the Cargo.
	*
	* Parameters:
	*	- load_time : The loading/unloading time of the Cargo.
	*
	* Returns: void.
	*/
	void SetLoadTime(int load_time);

	/*
	* Function: SetDelivereddTime.
	* Sets the time by which a cargo has been delivered.
	*
	* Parameters:
	*	- del_time : the time by which a cargo has been delivered.
	*
	* Returns: void.
	*/
	void SetDeliveredTime(Time del_time);
	
	/*
	* Function: SetWaitTime.
	* Sets the time the cargo waited until moving
	*
	* Parameters:
	*	- wait_time : the time the cargo waited until moving
	*
	* Returns: void.
	*/
	void SetWaitTime(Time wait_time);

	/*
	* Function: SetTruckID.
	* Sets the ID of the truck that moved it.
	*
	* Parameters:
	*	- id : the ID of the truck that moved it.
	*
	* Returns: void.
	*/
	void SetTruckID(int truck_id);

	/*
	* Function: SetDeliveryDistance.
	* Sets the delivery distance of the Cargo.
	*
	* Parameters:
	*	- delivery_distance : The delivery distance of the Cargo.
	*
	* Returns: void.
	*/
	void SetDeliveryDistance(double delivery_distance);
	
	/*
	* Function: SetCost.
	* Sets the cost of the Cargo
	*
	* Parameters:
	*	- cost : The cost of the Cargo.
	*
	* Returns: void.
	*/
	void SetCost(double cost);
	
	/*
	* Function: SetID.
	* Sets the ID of the Cargo.
	*
	* Parameters:
	*	- id : The id of the Cargo.
	*
	* Returns: void.
	*/
	void SetID(int id);


	Time GetWaitingTime() const;
	void SetWaitingTime(Time t);

};

#endif