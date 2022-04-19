#include "Time.h"

Time::Time() : days(0), hours(0) {}

Time::Time(int d, int h) {

	try 
	{
		if (d < 0) throw std::string("Days cannot be negative");
		if (h < 0 || h >= 24) throw std::string("Invalid Hour");
		this->days = d;
		this->hours = h;
	}
	catch (std::string e)
	{
		std::cout << "Value Error: " << e << std::endl;
		exit(1);
	}

}

Time::Time(int h)
{
	try 
	{
		if (h < 0) throw std::string("Hours Number cannot be negative!");

		this->hours = h % 24;
		this->days = (h - this->hours) / 24;


	}
	catch (std::string e)
	{
		std::cout << "Value Error: " << e << std::endl;
		exit(1);
	}
}

int Time::GetDay() const { return this->days; }
int Time::GetHour() const { return this->hours; }

void Time::SetDay(int d) {
	try 
	{
		if (d < 0) throw std::string("Days cannot be negative");
		this->days = d;
	}
	catch (std::string e)
	{
		std::cout << "Value Error: " << e << std::endl;
		exit(1);
	}
}

void Time::SetHour(int h) {
	try 
	{
		if (h < 0 || h >= 24) throw std::string("Invalid Hour");
		this->hours = h;
	}
	catch (std::string e)
	{
		std::cout << "Value Error: " << e << std::endl;
		exit(1);
	}
}


Time Time::operator-(Time other) {

	try {
		if ((this->days < other.days) || (this->days == other.days && this->hours < other.hours)) { throw std::string("Invalid operands!"); }

		int newDay, newHour;
		if (this->hours < other.hours) {
			newDay = this->days - other.days - 1;
			newHour = 24 - (other.hours - this->hours);
		}
		else {
			newDay = this->days - other.days;
			newHour = this->hours - other.hours;
		}
		Time t(newDay, newHour);
		return t;
	}
	catch (std::string e) {
		std::cout << e << std::endl;
		exit(1);
	}
}


Time Time::operator+(Time other) {
	int newDay, newHour;
	if (this->hours + other.hours >= 24) {
		newDay = this->days + other.days + 1;
		newHour = this->hours + other.hours - 24;
	}
	else {
		newDay = this->days + other.days;
		newHour = this->hours + other.hours;
	}

	Time t(newDay, newHour);
	return t;
}
