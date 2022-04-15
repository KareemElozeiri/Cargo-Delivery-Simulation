#ifndef NODE_H
#define NODE_H

template<typename T>
class Node
{
protected :
	T item;	// A data item (can be any complex structure)
	double priority; // Item's Priority in case there is
	Node<T>* next;	// Pointer to the next node

public :

	/*
	* Function: Node.
	* Default Constructor.
	*/
	Node()
	{
		this->next = nullptr;
	} 

	/*
	* Function: Node.
	* Non-Default Constructor.
	*/
	Node(T newItem, double priority = -1) // Non-default constructor
	{
		this->item = newItem;
		this->priority = priority;
		this->next = nullptr;
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
	* Function: setPriority.
	* Sets the priority of the node.
	*
	* Parameters:
	*	- priority : The priority value to be assigned to the node.
	*/
	void setPriority(double priority)
	{
		this->priority = priority;
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
	* Function: getPriority.
	* Returns the priority value of the node.
	*/
	double getPriority() const
	{
		return this->priority;
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
