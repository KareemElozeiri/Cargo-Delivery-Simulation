#include <iostream>
#include "Defs.h"

int main()
{
	Time t0(7, 6);
	Time t1(6, 6);
	Time t3 = t0 - t1;
	std::cout << t3.getDay() << " " << t3.getHour();
}

