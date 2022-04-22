#ifndef Time_H
#define Time_H
#include <iostream>

class Time {
private:
	int days;
	int hours;


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

	
	Time operator-(Time other);
	
	
	Time operator+(Time other);


	Time operator+(int added_hours);
	
	
	Time operator-(int subtracted_hours);
	

	/*
	* Function: SetDay.
	* setting the day in the time.
	*
	* Parameters:
	*	- day: the day need to be set
	*
	* Returns: void.
	*/
	void PrintTime() const;

};

#endif