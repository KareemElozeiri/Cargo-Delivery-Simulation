#ifndef CUSTOMS_H
#define CUSTOMS_H

#include <iostream>  
#include <string>  
#include "../SimulationAgents/Time.h"
using namespace std;
#define MAX 200

//int* splitInt(string str, int len);

string* split(string str, char ch);
Time splitTime(string str);



#endif