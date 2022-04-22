#ifndef LinkedList_CPP
#define LinkedList_CPP

#include "LinkedList.h"

template <typename T>
LinkedList<T>::LinkedList()
{
	Head = nullptr;
}

// List is being destructed ==> delete all items in the list
template <typename T>
LinkedList<T>::~LinkedList()
{
	DeleteAll();
}

template<typename T>
Node<T>* LinkedList<T>::GetHead()
{
	return this->Head;
}

template<typename T>
void LinkedList<T>::SetHead(Node<T>* Head) {
	this->Head = Head;
}

template <typename T>
void LinkedList<T>::InsertBeg(const T& data)
{
	Node<T>* R = new Node<T>(data);
	R->setNext(Head);
	Head = R;
}


template<typename T>
void LinkedList<T>::Insert(const T& data)
{
	Node<T>* newNode = new Node<T>(data);
	if (this->Head == nullptr) this->Head = newNode;
	else 
	{
		Node<T>* curr = this->Head;
		
		while (curr->getNext() != nullptr) curr = curr->getNext();
		curr->setNext(newNode);

	}
}

template <typename T>
void LinkedList<T>::DeleteAll()
{
	Node<T>* P = Head;
	while (Head)
	{
		P = Head->getNext();
		delete Head;
		Head = P;
	}
}

template<typename T>
void LinkedList<T>::DeleteFirst()
{
	if (this->Head != nullptr) {
		Node<T>* newHead = this->Head->getNext();
		delete this->Head;
		this->Head = nullptr;
		this->Head = newHead;
	}
}

template<typename T>
void LinkedList<T>::DeleteLast()
{
	Node<T>* curr = this->Head;
	if (this->Head != nullptr) {
		if (this->Head->getNext() != nullptr) {
			while (curr->getNext()->getNext() != nullptr)  curr = curr->getNext();
			Node<T>* last = curr->getNext();
			curr->setNext(nullptr);
			delete last;
		}
		else {
			delete this->Head;
			this->Head = nullptr;
		}
	}
}

template <typename T>
bool LinkedList<T>::Find(T Key) const {
	Node<T>* currentNode = this->Head;
	while (currentNode.getNext() != nullptr) {
		if (currentNode.getItem() == Key) {
			return true;
		}
		currentNode = currentNode.getNext();
	}
	return false;
}

template <typename T>
bool LinkedList<T>::DeleteNode(T value) {

	if (this->Head->getItem() == value) {
		Node<T>* nextNode = this->Head->getNext();
		// TODO
		// add delete head values
		delete this->Head;
		this->Head = nullptr;
		this->Head = nextNode;
		return true;
	}
	Node<T>* prevNode = this->Head;
	Node<T>* nextNode = this->Head->getNext()->getNext();
	while (prevNode->getNext() != nullptr) {
		if (prevNode->getNext()->getItem() == value) {
			prevNode->setNext(nextNode);
			return true;
		}
	}
	return false;
}
  
template <typename T>
bool LinkedList<T>::InsertSorted(T item) {
	if (this->Head->getItem() > item) {
		Node<T>* oldHead = this->Head;
		Node<T>* newHead = new Node<T>(item);
		delete this->Head;
		this->Head = nullptr;
		this->Head = newHead;
		this->Head->setNext(oldHead);
		return true;
	}

	Node<T>* prev = this->Head;
	Node<T>* next = this->Head->getNext();
	Node<T>* newNode = new Node<T>(item);
	while (next != nullptr) {
		if (item >= prev->getItem() && item <= next->getItem()) {
			prev->setNext(newNode);
			newNode->setNext(next);
			return true;
		}
		prev = prev->getNext();
		next = next->getNext();
	}
	next->setNext(newNode);
}

template<typename T>
bool LinkedList<T>::isEmpty() const
{
	return (this->Head==nullptr);
}

#endif