#include "LinkedList.h"
#include "Node.h"

template <class T>
LinkedList<T>::~LinkedList()
{
	// just goes throught the whole list and deletes everything
	Node<T> *tempPtr; 
	Node<T> *next;
	
	tempPtr = head;
	
	while (tempPtr != nullptr)
	{
		next = tempPtr->nextNode;
		delete tempPtr;
		tempPtr = next;
	}
	
}

template <class T>
void LinkedList<T>::append(T value)
{
	Node<T> *temp;
	Node<T> *tempPtr;
	
	temp = new Node<T>(value);
	if (head == nullptr) head = temp; // if its empty, then this appended node because the head.
	else
	{
		tempPtr = head;
		while (tempPtr->nextNode)
		{
			tempPtr = tempPtr->nextNode; // makes its way to the end of the linked list
		}
		
		tempPtr->nextNode = temp; // then adds it to the last nodes' nextnode pointer
	}
}

