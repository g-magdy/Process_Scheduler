#pragma once
#include <iostream>
#include "Node.h" // note that when including a file from the same folder (directory)
				  // I don't need to write "Basic/Node.h" (in fact this produces an error here)
template <class ItemType>
class LinkedList
{
	Node<ItemType>* headPtr;
	int count;
public:
	LinkedList();
	void insertBegin(const ItemType& entry);
	void insertEnd(const ItemType& entry);
	int length() const;
	void clear();
	void printlist() const;
	~LinkedList();
};

template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), count(0)
{
}

template<class ItemType>
void LinkedList<ItemType>::insertBegin(const ItemType& entry)
{
	Node<ItemType> * novel = new Node<ItemType>(entry); // novel means new (newly created node)
	novel->setNext(headPtr);
	headPtr = novel;
	count++;
}

template<class ItemType>
void LinkedList<ItemType>::insertEnd(const ItemType& entry)
{
	Node<ItemType>* novel = new Node<ItemType>(entry);
	novel->setNext(nullptr);
	
	if (headPtr == nullptr) // no elements in linked list
	{
		headPtr = novel;
	}
	else // list contains elements
	{
		Node<ItemType>* trav = headPtr; // trav is short for traverse (loop through)
		while (trav->getNext() != nullptr)
		{
			trav = trav->getNext();
		}
		// trav now points to the last elemnt 
		trav->setNext(novel);
	}
	count++;
}

template<class ItemType>
inline int LinkedList<ItemType>::length() const
{
	return count;
}

template<class ItemType>
inline void LinkedList<ItemType>::clear()
{
	if (headPtr == nullptr)
		return;

	Node <ItemType>* temp; // to destruct node
	while (headPtr != nullptr)
	{
		temp = headPtr;
		headPtr = headPtr->getNext();
		delete temp;
		count--;
	}
}

template<class ItemType>
inline void LinkedList<ItemType>::printlist() const
{
	Node<ItemType>* trav = headPtr;
	while (trav != nullptr)
	{
		std::cout << trav->getData() << " -> ";
		trav = trav->getNext();
	}
	std::cout << "NULL\n";
}

template<class ItemType>
inline LinkedList<ItemType>::~LinkedList()
{
	clear();
}
