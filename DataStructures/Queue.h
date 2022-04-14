#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"

template <typename T>
class Queue
{
private:
	LinkedList<T>* DataList = nullptr;

public:
	/*
	* Function: Queue.
	* The Queue Constructor.
	*/
	Queue();

	/*
	* Function: ~Queue.
	* The Queue Destructor.
	*/
	~Queue();
	
	/*
	* Function: enqueue.
	* Inserts a value at the beginning of the LinkedList.
	*
	* Parameters:
	*	- value : The value to be inserted in the LinkedList.
	*/
	void enqueue(T value);
	
	/*
	* Function: dequeue.
	* Removes the first element in the queue and assigns it to the a given reference variable of type T.
	*
	* Parameters:
	*	- value : This will hold the value of the first element in the queue.
	*/
	bool dequeue(T& value);

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

#include "Queue.cpp"

#endif