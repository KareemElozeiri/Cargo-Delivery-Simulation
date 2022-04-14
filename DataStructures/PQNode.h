#ifndef _PQNODE
#define _PQNODE

#include "Node.h"

template<typename T>
class PQNode : public Node<T>
{
private:
	double priority;

public :

	/*
	* Function: PQNode.
	* Default Constructor.
	*/
	PQNode()
	{
		this->setNext(nullptr);
	} 

	/*
	* Function: PQNode.
	* Non-Default Constructor.
	*/
	PQNode(T newItem) // Non-default constructor
	{
		this->setItem(newItem);
		this->setNext(nullptr);
	}

	/*
	* Function: setPriority.
	* Sets the priority of the node.
	*
	* Parameters:
	*	- priority : The priority value to be assigned to the node.
	*/
	void setPriority(double priority)
	{
		this->priority = priority;
	} 

	/*
	* Function: getPriority.
	* Returns the priority of the node.
	*/
	T getPriority() const
	{
		return this->priority;
	}

};

#endif