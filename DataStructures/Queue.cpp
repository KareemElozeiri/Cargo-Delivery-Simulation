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
	this->Data.InsertBeg(value);
}

template <typename T>
void Queue<T>::dequeue(T& value) {
	this->Data.GetHead(value);
	this->Data.DeleteFirst();
}

template <typename T>
void Queue<T>::peek(T& value) const {
	this->Data.GetHead(value);
}

template <typename T>
bool Queue<T>::isEmpty() const {
	T HeadValue;
	this->Data.GetHead(&HeadValue);
	return (HeadValue == nullptr);
}