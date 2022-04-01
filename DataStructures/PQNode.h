#pragma once

#include "Node.h"

template<typename T>
class PQNode: public Node<T>
{
private:
	double priority; // Item's Priority Value
public:

	void setPriority(double priority)
	{
		this->priority = priority;
		item = newItem;
	}

	double getPriority() const
	{
		return this->priority;
	}
};