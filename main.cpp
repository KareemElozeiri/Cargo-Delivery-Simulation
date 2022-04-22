#include "Company.h"
#include "SimulationAgents/Time.h"

int main()
{
	Time t(1, 1);
	t = t + 1;
	t.PrintTime();
}

