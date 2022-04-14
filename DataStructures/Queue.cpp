#ifndef QUEUE_CPP
#define QUEUE_CPP

#include "Queue.h"

template <typename T>
Queue<T>::Queue() {
	LinkedList<T>* DataList = new LinkedList<T>;
	this->DataList = DataList;
}

template <typename T>
Queue<T>::~Queue() {}

template <typename T>
void Queue<T>::enqueue(T value) {
	this->DataList->InsertBeg(value);
}

template <typename T>
bool Queue<T>::dequeue(T& value) {
	if (this->isEmpty())
		return 0;

	const Node<T>* Head = this->DataList->GetHead();
	value = Head->getItem();
	this->DataList->DeleteFirst();
	return 1;
}

template <typename T>
void Queue<T>::peek(T& value) const {
	this->DataList->GetHead(value);
}

template <typename T>
bool Queue<T>::isEmpty() const {
	return (this->DataList->GetHead() == nullptr);
}

#endif