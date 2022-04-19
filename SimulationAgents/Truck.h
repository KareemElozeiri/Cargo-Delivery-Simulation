#include "Time.h"
#include "../Defs.h"

class Truck {
private:
	TRUCKTYPE truck_type;
	int capacity;
	Time checkUpTime;
	double speed;
	Time deliveryInterval;

public:
	Truck(int capacity, Time checkUpTime, double speed);
	Truck(TRUCKTYPE truck_type, int capacity, Time checkUpTime,
		double speed, Time deliveryInterval);

	//getters
	TRUCKTYPE GetTruckType() const;
	int GetCapacity() const;
	Time GetCheckUpTime() const;
	double GetSpeed() const;
	Time GetDeliveryInterval() const;
	void CalculateDeliveryInterval();


};
