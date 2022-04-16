#include "Time.h"

class Truck {
private:
	int capacity;
	Time checkUpTime;
	double speed;
	Time deliveryInterval;

public:
	Truck(int capacity, Time checkUpTime, double speed);

	//getters
	Time GetCheckUpTime() const;
	int GetCapacity() const;
	double GetSpeed() const;
	Time GetDeliveryInterval() const;

	void CalculateDeliveryInterval();


};
