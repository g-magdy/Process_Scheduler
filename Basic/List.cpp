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