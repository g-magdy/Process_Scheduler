#pragma once
#include <iostream>
#include "Node.h" // note that when including a file from the same folder (directory) I don't need to write "Basic/Node.h" (in fact this produces an error here)
class Process;

template <class ItemType>
class List
{
	Node<ItemType>* head;
	Node<ItemType>* tail;
	int count;
public:
	List() : head(nullptr), tail(nullptr), count(0) {}	// default constructor : we will not use a copy constructor (No Objects are copied)

	void push_front(const ItemType& entry);			    // inserts new entry to front of the list in O(1)

	void push_back(const ItemType& entry);				// inserts new entry to end of the list in O(1)

	int getCount() const { return count; }				// returns num of elements

	bool isEmpty() const { return (count == 0); }

	void clear();

	void print() const;									// prints elements from head to tail separated with spaces and moves to new line at end

	ItemType front() const;							 	// [PLEASE CHECK that the list is not empty before calling it]: returns a copy of the first element (data of head)
	
	bool pop_front();									// Deallocates the first element from the list if exists
	bool pop_front(ItemType & item);					// Deallocates the first element from the list if exists and puts it in item
	
	bool pop_back();									// Deallocates the last element from the list if exists
	bool pop_back(ItemType& item);						// Deallocates the last element from the list if exists and puts it in item
	
	bool find(const ItemType& key) const;
	bool find(std::string ID) const;

	~List() { clear(); }
};

template<typename ItemType>
void List<ItemType>::push_front(const ItemType& entry)
{
	Node<ItemType>* novel = new Node<ItemType>(entry); // novel means new (newly created node)
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
inline void List<ItemType>::push_back(const ItemType& entry)
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
	{
		std::cout << trav->getData();
		if (trav->getNext())
			std::cout << ", ";
	}
}

template<class ItemType>
inline ItemType List<ItemType>::front() const
{
	if (isEmpty())
		throw "empty list";
	return head->getData();
}

template<class ItemType>
inline bool List<ItemType>::pop_front()
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
inline bool List<ItemType>::pop_front(ItemType& item)
{
	if (isEmpty())
		return false;

	item = head->getData();
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
inline bool List<ItemType>::pop_back()
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
inline bool List<ItemType>::pop_back(ItemType& item)
{
	if (isEmpty())
		return false;

	item = tail->getData();
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
inline bool List<ItemType>::find(const ItemType& key) const
{
	if (isEmpty())
		return false;

	Node<ItemType>* trav = head;
	while (trav)
	{
		if (trav->getData() == key)
			return true;
		trav = trav->getNext();
	}
	return false;
}

template<>
void List<Process*>::print() const;
template<>
bool List<Process*>::find(std::string ID) const;