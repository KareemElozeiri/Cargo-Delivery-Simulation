#include "../Defs.h"

class Truck {
private:
	int Capacity;
	Time CheckUpTime;
	double Speed;
	Time DeliveryInterval;

public:
	Truck(int capacity, Time checkUpTime, double speed);

	//getters
	Time getCheckUpTime() const;
	int getCapacity() const;
	double getSpeed() const;
	Time getDeliveryInterval() const;

	void CalculateDeliveryInterval();


};
