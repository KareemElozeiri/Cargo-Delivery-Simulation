#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"
#include <iostream>

template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)

public:
	LinkedList();
	~LinkedList();

	Node<T>* GetHead();
	void SetHead(Node<T>* Head);

	void PrintList() const;
	
	bool Find(T key) const;
	

	void InsertBeg(const T& data);
	bool InsertSorted(T item);

	void DeleteAll();
	void DeleteFirst();
	void DeleteLast();
	bool DeleteNode(T value);
	

	bool ShiftLargest();
	
};

#include "LinkedList.cpp"

#endif	

