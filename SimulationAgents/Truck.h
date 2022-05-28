#ifndef TRUCK_H
#define TRUCK_H

#include "Time.h"
#include "../Defs.h"
#include "../DataStructures/LinkedList.h"
#include "../DataStructures/Node.h"
#include "../DataStructures/PQueue.h"
#include "Cargo.h"



class Truck
{
private:
	TRUCKTYPE truck_type;
	CARGOTYPE cargo_type;

	int capacity;		// the number of cargos that the truck can carry at a time
	double speed;

	Time checkUpTime;	// the time consumed by the truck during maintenance 
	Time deliveryInterval; 
	Time first_delivered_cargo;
	Time CheckUpOutTime; // time to get out of the checkup
	Time total_load_time = 0;

	int maxjourneysBeforeCheckUp;
	int journeysBeforeCheckUp; // the number of journeys that the truck can make before its need of checkup
	int ID;
	double max_distance_to_deliver = 0;
	bool Loaded = false;
	bool Loading = false;
	double truck_priority = NULL;
	

	PQueue<Cargo*>* cargos = new PQueue<Cargo*>;


public:
	
	/*
	* Function: Truck.
	* The Truck Constructor.
	*
	* Parameters:
	*	- NO PARAMS.
	*/
	Truck();

	/*
	* Function: Truck.
	* The Truck Constructor.
	*
	* Parameters:
	*	- type : The Truck's type.
	*	- capacity: the capacity of the truck
	*	- checkUpTime: time taken before checkup
	*	- journeysBeforeCheckUp: journeys truck can make before checkup
	*	- speed: the truck's speed
	* 	- ID : The Truck's id.
	*/
	Truck(TRUCKTYPE truck_type, int capacity, Time checkUpTime, int journeysBeforeCheckUp, double speed, int id);

	/*
	* Function: GetTruckType.
	* gets the type of the truck.
	*
	* Parameters:
	*	- NO PARAMS
	*
	* Returns: TRUCKTYPE (ENUM of truck types).
	*/
	TRUCKTYPE GetTruckType() const;
	
	/*
	* Function: GetCapacity.
	* gets the capacity of the truck.
	*
	* Parameters:
	*	- NO PARAMS
	*
	* Returns: int.
	*/
	int GetCapacity() const;
	
	/*
	* Function: GetCheckUpTime.
	* gets the checkUpTime of a truck.
	*
	* Parameters:
	*	- NO PARAMS
	*
	* Returns: Time (class in Time.h).
	*/
	Time GetCheckUpTime() const;
	
	/*
	* Function: GetCapacity.
	* gets the speed of the truck.
	*
	* Parameters:
	*	- NO PARAMS
	*
	* Returns: double.
	*/
	double GetSpeed() const;
	
	/*
	* Function: GetCapacity.
	* gets the GetDeliveryInterval of the truck.
	*
	* Parameters:
	*	- NO PARAMS
	*
	* Returns: Time (class in Time.h).
	*/
	Time GetDeliveryInterval() const;
	
	/*
	* Function: GetJourneysBeforeCheckUp.
	* gets jounrneys Before CheckUp of the truck.
	*
	* Parameters:
	*	- NO PARAMS
	*
	* Returns: int.
	*/
	int GetJourneysBeforeCheckUp() const;
	
	/*
	* Function: CalculateDeliveryInterval.
	* calculated the delivery interval of the truck. and saves it in deliveryInterval.
	* 
	* The calculation:
	* 2* (maxDeliveryDistance/this->speed) + totalLoadTime
	* 
	* Parameters:
	*	- NO PARAMS
	*
	* Returns: void.
	*/
	void CalculateDeliveryInterval();

	/*
	* Function: GetID.
	* gets the ID of the truck.
	*
	* Parameters:
	*	- NO PARAMS
	*
	* Returns: int.
	*/
	int GetID() const;

	/*
	* Function: UpdateTruckPriority.
	* Updates the priority of the truck.
	*
	* Parameters:
	*	- NO PARAMS
	*
	* Returns: double.
	*/
	void UpdateTruckPriority(double delivery_distance);

	/*
	* Function: GetTruckPriority.
	* Gets the priority of the truck.
	*
	* Parameters:
	*	- NO PARAMS
	*
	* Returns: double.
	*/
	double GetTruckPriority() const;

	/*
	* Function: SetID.
	* Sets the ID of the Truck.
	*
	* Parameters:
	*	- id : The id of the Truck.
	*
	* Returns: void.
	*/
	void SetID(int id);
	/*
	*  Funtion: LoadCargo
	*  Handles the logic of loading a certain cargo on it
	*  Returns: true if the loading was done successfully false otherwise
	*/

	bool LoadCargo(Cargo* cargo);
	/*
	* Function: GetMinimumDeliveryTime
	* Returns: the time required to deliver the first cargo
	* on the truck where this first cargo has the minimum time required to deliver
	*/
	Time GetMinimumDeliveryTime() const;


	bool IsLoaded() const;

	void SetLoaded(bool value);


	bool IsLoading() const;
	void SetLoading(bool loading);


	void ResetJourneysCount();

	Time getCheckUpOutTime() const;
	void setCheckUpOutTime(Time time);


	CARGOTYPE GetCargoType() const;
	void SetCargoType(CARGOTYPE type);
};

#endif