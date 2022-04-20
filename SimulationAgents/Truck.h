#include "Time.h"
#include "../Defs.h"

class Truck {
private:
	TRUCKTYPE truck_type;
	int capacity;
	Time checkUpTime;
	double speed;
	Time deliveryInterval; 
	int jounrneysBeforeCheckUp;

public:
	Truck();
	//Truck(int capacity, Time checkUpTime, double speed);
	Truck(TRUCKTYPE truck_type, int capacity, Time checkUpTime, int journeysBeforeCheckUp, double speed); //Time deliveryInterval);

	//getters
	TRUCKTYPE GetTruckType() const;
	int GetCapacity() const;
	Time GetCheckUpTime() const;
	double GetSpeed() const;
	Time GetDeliveryInterval() const;
	int GetJourneysBeforeCheckUp() const;

	void CalculateDeliveryInterval();


};
