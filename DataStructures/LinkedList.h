#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"
#include <string>
#include <iostream>

template <typename T>
class LinkedList
{
private:
	Node<T>* Head;
	Node<T>* Tail;
	int count;

public:

	/*
	* Function: LinkedList.
	* Default-Constructor
	*/
	LinkedList();
	
	/*
	* Function: LinkedList.
	* Destructor
	*/
	~LinkedList();

	/*
	* Function: GetHead.
	* Returns a pointer to the head of the linkedlist.
	*/
	Node<T>* GetHead();

	/*
	* Function: SetHead.
	* Sets the head of the linkedlist.
	*
	* Parameters:
	*	- Head : The Node to be set as the head of the linkedlist.
	*/
	void SetHead(Node<T>* Head);

	/*
	* Function: PrintList.
	* Prints the values in the linkedlist.
	*/
	void PrintList() const;		
	
	/*
	* Function: Find.
	* Checks whether a given key exists in the linkedlist.
	*
	* Parameters:
	*	- key : The key to be looked for.
	*/
	bool Find(T key) const;
	
	/*
	* Function: InsertBeg.
	* Inserts a value at the beggining of the linkedlist.
	*
	* Parameters:
	*	- data : The value to be stored in the node.
	*/
	void InsertBeg(const T& data);

	/*
	* Function: Insert.
	* Inserts a value at the end of the linkedlist.
	*
	* Parameters:
	*	- data : The value to be stored in the node.
	*/
	void Insert(const T& data);
	
	/*
	* Function: InsertSorted.
	* Inserts a value in the linkedlist in its correctly sorted position.
	*
	* Parameters:
	*	- item : The value to be stored in the node.
	*/
	bool InsertSorted(T item);

	/*
	* Function: DeleteAll.
	* Deletes all the nodes from the linkedlist.
	*/
	void DeleteAll();

	/*
	* Function: DeleteFirst.
	* Deletes the first node in the linkedlist.
	*/
	void DeleteFirst();

	/*
	* Function: DeleteLast.
	* Deletes the last node in the linkedlist.
	*/
	void DeleteLast();
	
	/*
	* Function: DeleteNode.
	* Deletes a node with a given value from the linkedlist, if exists.
	*
	* Parameters:
	*	- value : The value to be looked for.
	*/
	bool DeleteNode(T value);	

	/*
	* Function: isEmpty.
	* Checks whether the linkedlist is empty.
	*/
	bool isEmpty() const;

	/*
	* Function: getCount.
	* Returns the number of nodes in the linkedlist.
	*
	* Returns: int.
	*/
	int getCount() const;

	/*
	* Function: getData.
	* Returns the data in the queue separated by commas.
	*
	* Returns: string.
	*/
	std::string getData() const;
};

#include "LinkedList.cpp"

#endif	

