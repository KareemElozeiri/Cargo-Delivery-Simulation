#include "Time.h"
#include "../Defs.h"
#include "../DataStructures/LinkedList.h"
#include "Cargo.h"
class Truck {
private:
	TRUCKTYPE truck_type;
	int capacity;		// the number of cargos that the truck can carry at a time
	Time checkUpTime;	// the time consumed by the truck during maintenance 
	double speed;
	Time deliveryInterval; 
	int jounrneysBeforeCheckUp; // the number of journeys that the truck can make before its need of checkup

	LinkedList<Cargo*> cargos;

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
