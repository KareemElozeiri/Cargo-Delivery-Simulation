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
		

	void InsertBeg(const T& data);
	void Insert(const T& data);

	void DeleteAll();
	void DeleteFirst();
	void DeleteLast();
	bool DeleteNode(T value);
	

	
};

#include "LinkedList.cpp"

#endif	

