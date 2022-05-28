#ifndef Time_H
#define Time_H

#include <iostream>
#include <string>
class Time
{
public:
	/*
	* Function: Time.
	* The Time Constructor.
	*
	* Parameters:
	*	- NO PARAMS.
	*/
	Time();

	/*
	* Function: Time.
	* The Time Constructor.
	*
	* Parameters:
	*	- day: the day in the date.
	*	- hour: the hour in that day
	*/
	Time(int day, int hour);
	
	/*
	* Function: Time.
	* The Time Constructor.
	*
	* Parameters:
	*	- hour: the hour in that day
	*/
	Time(int hour);

	/*
	* Function: GetDay.
	* gets the day in the time.
	*
	* Parameters:
	*	- NO PARAMS
	* 
	* Returns: int.
	*/
	int GetDay() const;
	
	/*
	* Function: GetDay.
	* gets the hour in the time.
	*
	* Parameters:
	*	- NO PARAMS
	*
	* Returns: int.
	*/
	int GetHour() const;
	
	/*
	* Function: GetTotalHours.
	* calculates the total number of hours in certain time
	* (24 * days  +  hours)
	*
	* Parameters:
	*	- NO PARAMS
	*
	* Returns: int.
	*/
	int GetTotalHours() const;

	/*
	* Function: SetDay.
	* setting the day in the time.
	*
	* Parameters:
	*	- day: the day need to be set
	*
	* Returns: void.
	*/
	void SetDay(int day);
	
	/*
	* Function: setHour.
	* setting the hour in the time.
	*
	* Parameters:
	*	- hour: the hour need to be set
	*
	* Returns: void.
	*/
	void SetHour(int hour);

	/*
	* Function: operator overloading (-).
	* overloading the negative sign to subtract 2 time classes from each others.
	*
	* Parameters:
	*	- other: the other time to be subtracted from the main time
	*
	* Returns: Time.
	*/
	Time operator-(Time other);

	/*
	* Function: operator overloading (+).
	* overloading the plus sign to added 2 time classes to each others.
	*
	* Parameters:
	*	- other: the other time to be added to the main time
	*
	* Returns: Time.
	*/
	Time operator+(Time other);
	
	/*
	* Function: operator overloading (+).
	* overloading the plus sign to added hours (int) to the time class.
	*
	* Parameters:
	*	- added_hours: the hours(int) to be added to the time
	*
	* Returns: Time.
	*/
	Time operator+(int added_hours);
	
	/*
	* Function: operator overloading (-).
	* overloading the negative sign to subtract hours(int) from a time class.
	*
	* Parameters:
	*	- subtracted_hours: the hours(int) to be subtracted from the time
	*
	* Returns: Time.
	*/
	Time operator-(int subtracted_hours);

	/*
	* Function: operator overloading (<).
	* overloading the less than operator to compare time objects.
	*
	* Parameters:
	*	- other_time : the time to be compared with the current one.
	*
	* Returns: Boolean.
	*/
	bool operator<(Time other_time);

	/*
	* Function: operator overloading (<=).
	* overloading the less than or equal operator to compare time objects.
	*
	* Parameters:
	*	- other_time : the time to be compared with the current one.
	*
	* Returns: Boolean.
	*/
	bool operator<=(Time other_time);

	/*
	* Function: operator overloading (>).
	* overloading the greater than operator to compare time objects.
	*
	* Parameters:
	*	- other_time : the time to be compared with the current one.
	*
	* Returns: Boolean.
	*/
	bool operator>(Time other_time);

	/*
	* Function: operator overloading (>=).
	* overloading the greater than or equal operator to compare time objects.
	*
	* Parameters:
	*	- other_time : the time to be compared with the current one.
	*
	* Returns: Boolean.
	*/
	bool operator>=(Time other_time);
	/*
	* Function: operator overloading (==).
	* overloading double equal operator to compare time objects.
	*
	* Parameters:
	*	- other_time : the time to be compared with the current one.
	*
	* Returns: Boolean.
	*/
	bool operator==(Time other_time);
	/*
	* Function: PrintTime.
	* printing the time in days and hours
	* ex: -->  5:15
	*
	* Parameters:
	*	- NO PARAMS.
	*
	* Returns: void.
	*/
	void PrintTime() const;


	std::string StringifyTime() const;

private:
	int days;
	int hours;
};

#endif