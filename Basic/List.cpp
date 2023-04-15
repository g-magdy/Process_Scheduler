#include "List.h"
#include "../Components/Process.h"

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
}

template<>
bool List<Process*>::find(std::string ID) const
{
	if (isEmpty())
		return false;

	Node<Process*>* trav = head;
	while (trav)
	{
		if (trav->getData()->getID() == ID)
			return true;
		trav = trav->getNext();
	}
	return false;
}

template<>
Process* List<Process*>::removeByID(std::string ID)
{
	if (isEmpty())
		return nullptr;

	Process* required = nullptr;
	
	if (head->getData()->getID() == ID)
	{
		required = head->getData();
		Node<Process*>* toDel = head;
		head = head->getNext();
		count--;
		delete toDel;
	}
	else
	{
		Node<Process*>* prev = head;
		Node<Process*>* trav = head->getNext();
		while (trav != nullptr)
		{
			if (trav->getData()->getID() == ID )
			{
				required = trav->getData();
				Node<Process*>* toDel = trav;
				trav = trav->getNext(); // the one after target
				prev->setNext(trav);
				delete toDel;
				count--;
				break;
			}
			prev = trav;
			trav = trav->getNext();
		}
	}

	return required;
}