#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"
#include <string>

template <typename T>
class Queue
{
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
	*
	* Returns: void.
	*/
	void enqueue(T value);
	
	/*
	* Function: dequeue.
	* Removes the first element in the queue and assigns it to the a given reference variable of type T.
	*
	* Parameters:
	*	- value : This will hold the value of the first element in the queue.
	*
	* Returns: boolean.
	*/
	bool dequeue(T& value);

	/*
	* Function: peek.
	* Assigns the value of the first element in the queue to a reference variable of type T.
	*
	* Parameters:
	*	- value : This will hold the value of the first element in the queue.
	*
	* Returns: void.
	*/
	void peek(T& value) const;
	
	/*
	* Function: isEmpty.
	* Checks Whether the queue is empty.
	*
	* Returns: boolean.
	*/
	bool isEmpty() const;

	/*
	* Function: getCount.
	* Returns the number of nodes in the queue.
	*
	* Returns: int.
	*/
	int getCount() const;

	/*
	* Function: getData.
	* Returns the data in the queue separated by commas.
	*
	* Returns: string.
	*/
	std::string getData() const;

protected:
	Node<T>* Head;
	Node<T>* Tail;
	int count;
};

#include "Queue.cpp"

#endif