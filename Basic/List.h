#pragma once
#include <iostream>
#include "Node.h" // note that when including a file from the same folder (directory)
// I don't need to write "Basic/Node.h" (in fact this produces an error here)
#include "../Components/Process.h"

template <class ItemType>
class List
{
	Node<ItemType>* head;
	Node<ItemType>* tail;
	int count;
public:
	// default constructor : we will not use a copy constructor (No Objects are copied)
	List() : head(nullptr), tail(nullptr), count(0)
	{}

	// inserts new entry to front of the list in O(1)
	void push_front(const ItemType& entry)
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

	// inserts new entry to end of the list in O(1)
	void push_back(const ItemType& entry)
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

	// returns num of elements 
	int getCount() const
	{
		return count;
	}

	bool isEmpty() const
	{
		return (count == 0);
	}

	void clear()
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

	// prints elements from head to tail separated with spaces and moves to new line at end
	void print() const
	{
		for (Node<ItemType>* trav = head; trav != nullptr; trav = trav->getNext())
		{
			std::cout << trav->getData();
			if (trav->getNext())
				std::cout << ", ";
		}
		std::cout << "\n";
	}

	// [PLEASE CHECK that the list is not empty before calling it]: returns a copy of the first element (data of head)
	ItemType front() const
	{
		return head->getData();
	}
	// Deallocates the first element from the list if exists
	bool pop_front()
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
	// Deallocates the last element from the list if exists
	bool pop_back()
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

	~List()
	{
		clear();
	}

};

template<>
void List<Process*>::print() const
{
	if (isEmpty())
		return;

	for (Node<Process*>* trav = head; trav; trav = trav->getNext())
	{
		std::cout << *(trav->getData());
		if (trav->getNext())
			std::cout << ", ";
	}
	std::cout << "\n";
}