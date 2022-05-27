#ifndef CARGO_H
#define CARGO_H

#include "Time.h"
#include "../Defs.h"

class Cargo
{
public:
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
	* Sets the cost of the Cargo.
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

private:
	CARGOTYPE Cargo_type;
	int cargoID;
	Time preparation_time;
	int load_time;
	double delivery_distance;
	double cost;
};

#endif