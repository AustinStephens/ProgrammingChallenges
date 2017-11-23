#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

// A linked list template, since there are none implemented in c++, and I can make it wayyyyy smaller for what I need.
template <class T>
class LinkedList
{
public:
	Node<T> *head; // pointer to the first node
	
	LinkedList()
	{
		head = nullptr; 
	}
	
	~LinkedList();
	
	void append(T);
};
#endif
