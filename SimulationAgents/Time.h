#ifndef Time_H
#define Time_H
#include <iostream>

class Time {
private:
	int day;
	int hour;


public:
	Time();
	Time(int d, int h);

	
	int GetDay() const;
	int GetHour() const;

	
	void SetDay(int d);
	void SetHour(int h);

	Time operator-(Time other);
	Time operator+(Time other);

};

#endif