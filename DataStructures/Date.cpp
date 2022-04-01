#include "Date.h"

Date::Date()
{
	day = 0;
	hour = 0;
}

Date::Date(int p_day, int p_hour)
{
	day = p_day;
	hour = p_hour;
}

Date::Date(const Date& member)
{
	day = member.day;
	hour = member.hour;
}

Date Date::operator+(Date secondDate)
{
	Date result;
	result.day = day + secondDate.day;
	result.hour = hour + secondDate.hour;
	return result;
}

int Date::getDay()
{
	return day;
}

int Date::getHour()
{
	return hour;
}

void Date::setDay(int p_day)
{
	day = p_day;
}

void Date::setHour(int p_hour)
{
	hour = p_hour;
}