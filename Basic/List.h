#pragma once
#include <iostream>
#include "Node.h" // note that when including a file from the same folder (directory)
// I don't need to write "Basic/Node.h" (in fact this produces an error here)

template <class ItemType>
class List
{
	Node<ItemType>* head;
	Node<ItemType>* tail;
	int count;
public:
	// default constructor
	List(); // we will not use a copy constructor (No Objects are copied)
	// inserts new entry to front of the list in O(1)
	void insertBegin(const ItemType& entry);
	// inserts new entry to end of the list in O(1)
	void insertEnd(const ItemType& entry);
	// returns num of elements 
	int getCount() const;
	
	bool isEmpty() const;

	void clear();
	// prints elements from head to tail separated with spaces and moves to new line at end
	void print() const;
	// [PLEASE CHECK that the list is not empty before calling it]: returns a copy of the first element (data of head)
	ItemType front() const;
	// Deallocates the first element from the list if exists
	bool removeFront();
	// Deallocates the last element from the list if exists
	bool removeLast();


	~List();
};

template<class ItemType>
List<ItemType>::List() : head(nullptr), tail(nullptr), count(0)
{
}

template<class ItemType>
void List<ItemType>::insertBegin(const ItemType& entry)
{
	Node<ItemType> * novel = new Node<ItemType>(entry); // novel means new (newly created node)
	if (head == nullptr) // the list is empty
	{
		head = tail = novel;
	}
	else
	{
		novel->setNext(head);
		head = novel;
	}
	count++;
}

template<class ItemType>
void List<ItemType>::insertEnd(const ItemType& entry)
{
	Node<ItemType>* novel = new Node<ItemType>(entry);
	if (head == nullptr)
	{
		head = tail = novel;
	}
	else
	{
		tail->setNext(novel);
		tail = novel;
	}
	count++;
}

template<class ItemType>
inline int List<ItemType>::getCount() const
{
	return count;
}

template<class ItemType>
inline bool List<ItemType>::isEmpty() const
{
	return (count == 0);
}

template<class ItemType>
inline void List<ItemType>::clear()
{
	if (head == nullptr)
		return;

	Node <ItemType>* temp; // to destruct node
	while (head != nullptr)
	{
		temp = head;
		head = head->getNext();
		delete temp;
		count--;
	}
}

template<class ItemType>
inline void List<ItemType>::print() const
{
	for (Node<ItemType>* trav = head; trav != nullptr; trav = trav->getNext())
		std::cout << trav->getData() << " ";
	std::cout << "\n";
}

template<class ItemType>
inline ItemType List<ItemType>::front() const
{
	return head->getData();
}

template<class ItemType>
inline bool List<ItemType>::removeFront()
{
	if (isEmpty())
		return false;

	if (head == tail) // a single element exists
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
		Node<ItemType>* toDel = head;
		head = head->getNext();
		delete toDel;
	}
	count--;
	return true;
}

template<class ItemType>
inline bool List<ItemType>::removeLast()
{
	if (isEmpty())
		return false;

	if (head == tail) // only one element
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
		Node<ItemType>* trav = head;
		while (trav->getNext() != tail) // stop when trav points to the one before last
			trav = trav->getNext();
		
		trav->setNext(nullptr); // mark new end
		Node<ItemType>* toDel = tail;
		delete toDel;
		tail = trav; // now tail has moved to the one before last
	}
	count--;
	return true;
}

template<class ItemType>
inline List<ItemType>::~List()
{
	clear();
}
