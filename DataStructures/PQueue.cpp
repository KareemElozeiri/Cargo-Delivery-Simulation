#ifndef PQUEUE_CPP
#define PQUEUE_CPP

#include "PQueue.h"

template <typename T>
PQueue<T>::PQueue() {
	this->Head = nullptr;
	this->Tail = nullptr;
}

template <typename T>
PQueue<T>::~PQueue() {
	Node<T>* tempNode = this->Head;
	while(this->Head) {
		tempNode = this->Head->getNext();
		delete this->Head;
		this->Head = tempNode;
	}
}

template <typename T>
void PQueue<T>::enqueue(T value, double priority) {
	Node<T>* newNode = new Node<T>;
	newNode->setItem(value);
	newNode->setPriority(priority);

	if (this->Tail == nullptr) {
		this->Tail = newNode;
		this->Head = newNode;
		this->count += 1;
		return;
	}

	if (this->Head == nullptr || this->Head->getPriority() <= priority) {
		newNode->setNext(this->Head);
		this->Head = newNode;
		this->count += 1;
		return;
	}
	
	Node<T>* currentPtr = this->Head;
	Node<T>* loopingPtr = this->Head->getNext();

	if (loopingPtr == nullptr) {
		this->count += 1;
		newNode->setNext(nullptr);
		this->Head->setNext(newNode);
		return;
	}
	
	while (loopingPtr) {
		if (loopingPtr->getPriority() <= priority) {
			newNode->setNext(loopingPtr);
			currentPtr->setNext(newNode);
			this->count += 1;
			return;
		}
		if (loopingPtr->getNext() == nullptr) {
			loopingPtr->setNext(newNode);
			newNode->setNext(nullptr);
			this->Tail = newNode;
			this->count += 1;
			return;
		}
		currentPtr = loopingPtr;
		loopingPtr = currentPtr->getNext();
	}
}

#endif