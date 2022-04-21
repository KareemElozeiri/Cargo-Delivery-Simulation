#ifndef LinkedList_CPP
#define LinkedList_CPP

#include "LinkedList.h"

template <typename T>
LinkedList<T>::LinkedList()
{
	Head = nullptr;
}

//List is being desturcted ==> delete all items in the list
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

/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
template <typename T>
void LinkedList<T>:: PrintList()	const
{
	std::cout << "\nprinting list contents:\n\n";
	Node<T>* p = Head;

	while (p)
	{
		std::cout << "[ " << p->getItem() << " ]";
		std::cout << "--->";
		p = p->getNext();
	}
	std::cout << "*\n";
}


/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
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


/*
* Function: DeleteAll.
* Deletes all nodes of the list.
*/
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

// Deletes the head of the linked list
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

//Deletes the tail of the linked list
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


//deletes the first node with the given value(if found) and returns true
//if not found, returns false
//Note: List is not sorted
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

template<typename T>
bool LinkedList<T>::isEmpty() const
{
	return (this->Head==nullptr);
}

#endif