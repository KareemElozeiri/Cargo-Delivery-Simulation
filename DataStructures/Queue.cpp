#ifndef QUEUE_CPP
#define QUEUE_CPP

#include "Queue.h"

template <typename T>
Queue<T>::Queue() {
	this->Head = nullptr;
	this->Tail = nullptr;
	this->count = 0;
}

template <typename T>
Queue<T>::~Queue() {
	Node<T>* tempNode = Head;
	while(this->Head) {
		tempNode = Head->getNext();
		delete Head;
		Head = tempNode;
	}
	this->count = 0;
}

template <typename T>
void Queue<T>::enqueue(T value) {
	Node<T>* newNode = new Node<T>(value);
	
	if (Tail == nullptr) {
		this->Head = newNode;
		this->Tail = newNode;
		this->count += 1;
		return;
	}

	Tail->setNext(newNode);
	Tail = newNode;
	this->count += 1;
}

template <typename T>
bool Queue<T>::dequeue(T& value) {
	if (this->isEmpty())
		return 0;

	value = this->Head->getItem();
	Node<T>* tempNode = this->Head;
	this->Head = this->Head->getNext();
	delete tempNode;
	this->count -= 1;

	return 1;
}

template <typename T>
void Queue<T>::peek(T& value) const {
	if (this->isEmpty())
		return;
	value = this->Head->getItem();
}

template <typename T>
bool Queue<T>::isEmpty() const {
	return (this->Head == nullptr);
}

template <typename T>
int Queue<T>::getCount() const {
	return this->count;
}

template <typename T>
std::string Queue<T>::getData() const {
	std::string QueueData;
	Node<T>* loopingPtr = this->Head;
	while (loopingPtr != nullptr)
	{
		QueueData += loopingPtr->getItem()->GetID();
		if (loopingPtr->getNext() != nullptr) {
			QueueData += ",";
		}
		loopingPtr = loopingPtr->getNext();
	}
	return QueueData;
}

#endif