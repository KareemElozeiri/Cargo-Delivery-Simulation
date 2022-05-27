#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <string>

template <typename T>
class LinkedList
{
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
	*
	* Returns: Node*.
	*/
	Node<T>* GetHead();

	/*
	* Function: SetHead.
	* Sets the head of the linkedlist.
	*
	* Parameters:
	*	- Head : The Node to be set as the head of the linkedlist.
	*
	* Returns: void.
	*/
	void SetHead(Node<T>* Head);

	/*
	* Function: PrintList.
	* Prints the values in the linkedlist.
	*
	* Returns: void.
	*/
	void PrintList() const;		
	
	/*
	* Function: Find.
	* Checks whether a given key exists in the linkedlist.
	*
	* Parameters:
	*	- key : The key to be looked for.
	*
	* Returns: boolean.
	*/
	bool Find(T key) const;
	
	/*
	* Function: InsertBeg.
	* Inserts a value at the beggining of the linkedlist.
	*
	* Parameters:
	*	- data : The value to be stored in the node.
	*
	* Returns: void.
	*/
	void InsertBeg(const T& data);

	/*
	* Function: Insert.
	* Inserts a value at the end of the linkedlist.
	*
	* Parameters:
	*	- data : The value to be stored in the node.
	*
	* Returns: void.
	*/
	void Insert(const T& data);
	
	/*
	* Function: InsertSorted.
	* Inserts a value in the linkedlist in its correctly sorted position.
	*
	* Parameters:
	*	- item : The value to be stored in the node.
	*
	* Returns: boolean.
	*/
	bool InsertSorted(T item);

	/*
	* Function: DeleteAll.
	* Deletes all the nodes from the linkedlist.
	*
	* Returns: void.
	*/
	void DeleteAll();

	/*
	* Function: DeleteFirst.
	* Deletes the first node in the linkedlist.
	*
	* Returns: void.
	*/
	void DeleteFirst();

	/*
	* Function: DeleteLast.
	* Deletes the last node in the linkedlist.
	*
	* Returns: void.
	*/
	void DeleteLast();
	
	/*
	* Function: DeleteNode.
	* Deletes a node with a given value from the linkedlist, if exists.
	*
	* Parameters:
	*	- value : The value to be looked for.
	*
	* Returns: boolean.
	*/
	bool DeleteNode(T value);	

	/*
	* Function: isEmpty.
	* Checks whether the linkedlist is empty.
	*
	* Returns: boolean.
	*/
	bool isEmpty() const;

	/*
	* function: getcount.
	* returns the number of nodes in the linkedlist.
	*
	* returns: int.
	*/
	int getCount() const;

	void setCount(int value);

	/*
	* Function: getData.
	* Returns the data in the queue separated by commas.
	*
	* Returns: string.
	*/
	std::string getData() const;

private:
	Node<T>* Head;
	Node<T>* Tail;
	int count;
};

#include "LinkedList.cpp"

#endif