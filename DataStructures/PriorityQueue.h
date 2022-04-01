#pragma once

#include "PQNode.h"

template <typename T>
class PQueue
{
private:
	PQNode<T>* Head = nullptr;
	int counter = 0;

public:
	/*
	* Function: PQueue.
	* The PQueue Constructor.
	*/
	PQueue();

	/*
	* Function: ~PQueue.
	* The PQueue Destructor.
	*/
	~PQueue();

	/*
	* Function: enqueue.
	* Inserts a value in the queue based on its priority.
	*
	* Parameters:
	*	- value : The value to be inserted in the queue.
	*/
	void enqueue(T value, double priority);

	/*
	* Function: dequeue.
	* Removes the first element in the queue and assigns it to the a given reference variable of type T.
	*
	* Parameters:
	*	- value : This will hold the value of the first element in the queue.
	*/
	void dequeue(T& value);

	/*
	* Function: peek.
	* Assigns the value of the first element in the queue to a reference variable of type T.
	*
	* Parameters:
	*	- value : This will hold the value of the first element in the queue.
	*/
	void peek(T& value) const;

	/*
	* Function: isEmpty.
	* Checks Whether the queue is empty.
	*
	* Returns: boolean.
	*/
	bool isEmpty() const;
};