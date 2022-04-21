#ifndef Time_H
#define Time_H
#include <iostream>

class Time {
private:
	int days;
	int hours;


public:
	Time();
	Time(int d, int h);
	Time(int h);
	
	int GetDay() const;
	int GetHour() const;

	
	void SetDay(int d);
	void SetHour(int h);

	Time operator-(Time other);
	Time operator+(Time other);


	Time operator+(int added_hours);
	Time operator-(int subtracted_hours);
	
	void PrintTime() const;

};

#endif