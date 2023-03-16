#include "Node.h"
#include <iostream>

template<typename itemType>
class Queue
{
	Node<itemType>* front,* back;
	int itemCount;

public:
	Queue()
	{
		front = back = nullptr;
		itemCount = 0;
	}
	Queue(const Queue& second)
	{
		// equaling the itemCount
		itemCount = second.itemCount;

		// making a pointer to copy all the elements of the second Queue
		Node<itemType>* copyPtr = second.front;

		while (copyPtr)
		{
			push(copyPtr->getData());
			copyPtr = copyPtr->getNext();
		}
	}
	bool push(itemType data)
	{
		//creating a new node
		Node<itemType>* newNode = new Node<itemType>(data);
		newNode->setNext(nullptr);

		if (!front)
		{
			front = back = newNode;
		}
		else
		{
			back->setNext(newNode);
			back = newNode;
		}

		//increment the itemCount
		itemCount++;

		return true;
	}
	bool pop()
	{
		if (empty())
			return false;

		// catching the front with a temp pointer
		Node<itemType>* delPtr = front;
		front = front->getNext();

		// delete old front
		delete delPtr;

		//decrese itemCount
		itemCount--;

		return true;
	}
	bool pop(itemType& data)
	{
		if (empty())
			return false;

		// catching the front with a temp pointer
		Node<itemType>* delPtr = front;
		front = front->getNext();

		//put the front item in "data" before deleting
		data = delPtr->getData();

		// delete old front
		delete delPtr;

		//decrese itemCount
		itemCount--;

		return true;
	}
	bool empty()
	{
		return itemCount == 0;
	}
	itemType Front()
	{
		if (front)
			return front->getData();

		//what should I return if front was null?
		return 0;
	}
	itemType Back()
	{
		if (back)
			return back->getData();

		//what should I return if back was null?
		return 0;
	}
	int size()
	{
		return itemCount;
	}
	void print()
	{
		if (empty())
			return;

		Node<itemType>* cur = front;
		while (cur)
		{
			std::cout << "[" << cur->getData() << "]-->";
			cur = cur->getNext();
		}
		std::cout << "NULL";
	}
};

