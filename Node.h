#ifndef NODE_H
#define NODE_H


// A single node of a linked list
template <class T>
class Node
{
public:
	T value;
	Node<T> *nextNode; // pointer to the next node
	
	Node (T nodeVal) // sets the value and initializes the nextnode to null
	{
		value = nodeVal;
		nextNode = nullptr;
	}	
};
#endif
