#ifndef _NODE
#define _NODE

template<typename T>
class Node
{
protected :
	T item;	// A data item (can be any complex structure)
	Node<T>* next;	// Pointer to the next node

public :

	/*
	* Function: Node.
	* Default Constructor.
	*/
	Node()
	{
		next = nullptr;
	} 

	/*
	* Function: Node.
	* Non-Default Constructor.
	*/
	Node(T newItem) // Non-default constructor
	{
		item = newItem;
		next = nullptr;
	}
	
	/*
	* Function: setItem.
	* Sets the value of the node.
	*
	* Parameters:
	*	- newItem : The value to be stored in the node.
	*/
	void setItem(T newItem)
	{
		item = newItem;
	}

	/*
	* Function: setNext.
	* Sets the next pointer of the node.
	*
	* Parameters:
	*	- nextNodePtr : The pointer to be stored as the next pointer to the node.
	*/
	void setNext(Node<T>* nextNodePtr)
	{
		next = nextNodePtr;
	} 

	/*
	* Function: getItem.
	* Returns the value of the node item.
	*/
	T getItem() const
	{
		return this->item;
	}

	/*
	* Function: getNext.
	* Returns the pointer to the next node.
	*/
	Node<T>* getNext() const
	{
		return this->next;
	}

};

#endif	
