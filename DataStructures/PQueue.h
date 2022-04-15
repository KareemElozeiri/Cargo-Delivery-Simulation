#ifndef PQUEUE_H
#define PQUEUE_H

#include "Queue.h"

template <typename T>
class PQueue : public Queue<T>
{
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
};

#include "PQueue.cpp"

#endif