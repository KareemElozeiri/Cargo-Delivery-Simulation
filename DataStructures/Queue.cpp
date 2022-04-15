#ifndef QUEUE_CPP
#define QUEUE_CPP

#include "Queue.h"

template <typename T>
Queue<T>::Queue() {
	this->Head = nullptr;
	this->Tail = nullptr;
}

template <typename T>
Queue<T>::~Queue() {
	Node<T>* tempNode = Head;
	while(this->Head) {
		tempNode = Head->getNext();
		delete Head;
		Head = tempNode;
	}
}

template <typename T>
void Queue<T>::enqueue(T value) {
	Node<T>* newNode = new Node<T>(value);
	
	if (Tail == nullptr) {
		this->Head = newNode;
		this->Tail = newNode;
		return;
	}

	Tail->setNext(newNode);
	Tail = newNode;
}

template <typename T>
bool Queue<T>::dequeue(T& value) {
	if (this->isEmpty())
		return 0;

	value = this->Head->getItem();
	Node<T>* tempNode = this->Head;
	this->Head = this->Head->getNext();
	delete tempNode;

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

#endif