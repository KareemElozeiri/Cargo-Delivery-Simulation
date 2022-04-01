#include "CargoTypeTest1.h"

Date CargoTypeTest::getPrepTime()
{
	return preparation_time;
}

int CargoTypeTest::getLoadTime()
{
	return load_time;
}

double CargoTypeTest::getDeliveryDistance()
{
	return delivery_distance;
}

double CargoTypeTest::getCost()
{
	return cost;
}

int CargoTypeTest::getID()
{
	return CargoID;
}
