#pragma once
#pragma once
#include"Node.h"
template<class itemType>
class stack
{
private:
	int itemCount;
	Node<itemType>* Top;
public:
	stack() {
		itemCount = 0;
		Top = nullptr;
	}


	stack(const itemType& data) {
		Node<itemType>* ptr = new Node<itemType>(data);
		Top = ptr;
		itemCount = 1;
	}


	/// will we need copy constructor 

	stack(const stack<itemType>& toCopy) {

		itemCount = toCopy.itemCount;
		if (itemCount == 0) {
			Top = nullptr;
		}
		else
		{
			Node<itemType>* temptr1 = new Node<itemType>(toCopy.Top->getData());
			Top = temptr1;
			Node <itemType>* toCopyTemp = toCopy.Top->getNext();
			while (toCopyTemp)
			{
				//create new node 
				// temp2 stand for the current stack
				//temp1 stand for the stack to copy data from 

				Node<itemType>* temptr2 = new Node<itemType>(toCopyTemp->getData());
				temptr1->setNext(temptr2);
				temptr1 = temptr1->getNext();

				toCopyTemp = toCopyTemp->getNext();
			}
			temptr1->setNext(nullptr);
		}

	}
	itemType top() {
		//there might be exception handling 
		if (Top)
			return Top->getData();
	}

	bool push(const itemType& data) {
		Node<itemType>* newnode = new Node<itemType>(data);
		newnode->setNext(Top);
		Top = newnode;
		itemCount++;
		return 1;
	}
	bool pop(itemType& data) {
		if (empty())
		{
			return 0;
		}



		Node<itemType>* todelete = Top;
		data = Top->getData();
		Top = Top->getNext();
		itemCount--;
		delete todelete;
		return 1;
	}
	bool pop() {
		if (empty())
		{
			return 0;
		}
		Node<itemType>* todelete = Top;
		Top = Top->getNext();
		itemCount--;
		delete todelete;
		return 1;
	}

	int size() {
		return itemCount;
	}


	bool empty() {
		return (itemCount == 0);
	}


	void print() {
		if (empty())
			return;
		Node<itemType>* temp = Top;

		while (temp)
		{
			std::cout << "[" << temp->getData() << "]-->";
			temp = temp->getNext();
		}
		std::cout << "NULL";
	}
};

