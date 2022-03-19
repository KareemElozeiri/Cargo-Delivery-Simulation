#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"
#include <iostream>
using namespace std;

template <typename T>
class LinkedList
{
private:
	Node<T> *Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
public:


	LinkedList()
	{
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{
		cout<<"\nprinting list contents:\n\n";
		Node<T> *p = Head;

		while(p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "*\n";
	}
	
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	* 
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
	}
	
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T> *P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}

	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(T Key) const {
		Node<T> *currentNode = this->Head;
		while (currentNode.getNext() != nullptr) {
			if (currentNode.getItem() == Key) {
				return true;
			}
			currentNode = currentNode.getNext();
		}
		return false;
	};


	//[3]CountOccurance
	//returns how many times a certain value appeared in the list

	//[4] DeleteFirst
	//Deletes the first node in the list

	//[5] DeleteLast
	//Deletes the last node in the list

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(T value) {

		if (this->Head->getItem() == value) {
			Node<T> *nextNode = this->Head->getNext();
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

	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted

	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L

	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)

	//insert in a sorted list
	bool InsertSorted(T item) {
		if (this->Head->getItem() > item) {
			Node<T> *oldHead = this->Head;
			Node<T> *newHead = new Node<T>(item);
			delete this->Head;
			this->Head = nullptr;
			this->Head = newHead;
			this->Head->setNext(oldHead);
			return true;
		}

		Node<T> *prev = this->Head;
		Node<T> *next = this->Head->getNext();
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


	bool ShitLargest() {
		Node<T> *prev = this->Head;
		Node<T> *curr = prev->getNext();
		Node<T>* next = curr->getNext();

		if (prev->getItem() > curr->getItem()) {
			this->Head = curr;
			this->Head->setNext(prev);
			prev->setNext(next);
		}
		this->PrintList();

		prev = this->Head;
		curr = prev->getNext();
		next = curr->getNext();


		Node<T> *nextOfNext = next->getNext();
		while (nextOfNext != nullptr) {

			if (curr->getItem() > next->getItem()) {
				prev->setNext(next);
				next->setNext(curr);
				curr->setNext(nextOfNext);
			}

			this->PrintList();


			prev = prev->getNext();
			curr = prev->getNext();
			next = curr->getNext();
			nextOfNext = next->getNext();

		}

		if (curr->getItem() > next->getItem()) {
			prev->setNext(next);
			next->setNext(curr);
			curr->setNext(nullptr);

		}

		return true;
	}

	void Reorder_X(T x) {
		
	}

};

#endif	
