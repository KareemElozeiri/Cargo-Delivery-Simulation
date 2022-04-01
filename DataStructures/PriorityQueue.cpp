#include "PriorityQueue.h"

template <typename T>
PQueue<T>::PQueue() {}

template <typename T>
PQueue<T>::~PQueue() {}

template <typename T>
void PQueue<T>::enqueue(T value, double priority) {
	PQNode<T>* newNode = new PQNode<T>;
	newNode->setItem(value);
	newNode->setPriority(priority);

	if (this->Head == nullptr) {
		newNode->setNext(this->Head);
		this->Head = newNode;
		return;
	}

	if (this->Head->getPriority() < priority) {
		newNode->setNext(this->Head);
		this->Head = newNode;
		return;
	}

	PQNode<T>* loopingPtr = this->Head;
	PQNode<T>* currentPtr = this->Head->getNext();
	
	while (loopingPtr) {
		if (currentPtr->getNext() == nullptr) {
			currentPtr->setNext(newNode);
			newNode->setNext(nullptr);
			return;
		}
		if (loopingPtr->getPriority() < priority) {
			newNode->setNext(loopingPtr);
			currentPtr->setNext(newNode);
			return;
		}
		currentPtr = loopingPtr;
		loopingPtr = currentPtr->getNext();
	}
}

template <typename T>
void PQueue<T>::dequeue(T& value) {
	if (this->Head == nullptr)
		return;

	value = this->Head->getItem();
	PQNode<T>* tempNode = this->Head->getNext();
	delete this->Head;
	this->Head = tempNode;
}

template <typename T>
void PQueue<T>::peek(T& value) const {
	if (this->Head == nullptr)
		return;

	value = this->Head->getItem();
}

template <typename T>
bool PQueue<T>::isEmpty() const {
	return (this->Head == nullptr);
}