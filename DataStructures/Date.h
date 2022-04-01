#pragma once
class Date
{
	int day;
	int hour;

public:
	Date();
	Date(int p_day, int p_hour);
	Date(const Date &member);
	Date operator + (Date secondDate);

	int getDay();
	int getHour();
	void setDay(int d);
	void setHour(int h);
	


};

