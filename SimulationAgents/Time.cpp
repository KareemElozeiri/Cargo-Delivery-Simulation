#ifndef TIME_CPP
#define TIME_CPP

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

int Time::GetTotalHours() const
{
	return this->hours + 24 * this->days;
}

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

// Adding hours to the current time (Overloading the + operator for int)
Time Time::operator+(int added_hours) {
	int newDay, newHour;

	// Divinding the added_hours into days & hours, in case it's more than 24
	int added_days = added_hours / 24;
	added_hours = added_hours % 24;

	if (this->hours + added_hours >= 24) {
		newDay = this->days + 1 + added_days;
		newHour = this->hours + added_hours - 24;
	}
	else {
		newDay = this->days + added_days;
		newHour = this->hours + added_hours;
	}

	Time t(newDay, newHour);
	return t;
}

// Subtracting hours from the current time (Overloading the - operator for int)
Time Time::operator-(int subtracted_hours){
	// Handling the case when the subtracted hours are more than 24.
	int subtracted_days = subtracted_hours / 24;
	subtracted_hours = subtracted_hours % 24;
	Time tempTime(subtracted_days, subtracted_hours);

	try {
		int total_hours = this->days * 24 + this->hours;
		if (total_hours < subtracted_hours) { throw std::string("Invalid operands!"); }

		int newDay, newHour;
		if (this->hours < subtracted_hours) {
			newDay = this->days - tempTime.days - 1;
			newHour = 24 - (tempTime.hours - this->hours);
		}
		else {
			newDay = this->days - tempTime.days;
			newHour = this->hours - tempTime.hours;
		}
		Time t(newDay, newHour);
		return t;
	}
	catch (std::string e) {
		std::cout << e << std::endl;
		exit(1);
	}
}

bool Time::operator<(Time other_time) {

	return (this->days * 24 + this->hours) < (other_time.days * 24 + other_time.hours);
}

bool Time::operator>(Time other_time) {
	return (other_time < *this);
}

void Time::PrintTime() const
{
	std::cout << this->days << ":" << this->hours << std::endl;
}

#endif