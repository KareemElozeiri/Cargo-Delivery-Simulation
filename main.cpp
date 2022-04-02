#include <iostream>
#include "Defs.h"
#include "DataStructures/LinkedList.h"

int main()
{
	LinkedList<int> L;	//create an object of class LinkedList
	int val;

	std::cout << "\nPlease enter int values to add to the list (-1 to stop):\n";
	std::cin >> val;
	while (val != -1)
	{
		L.InsertBeg(val);
		std::cin >> val;
	}
	
	L.PrintList();
	L.DeleteFirst();
	L.DeleteLast();
	L.PrintList();

	return 0;
}

