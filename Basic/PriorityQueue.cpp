#include "PriorityQueue.h"
#include "../Components/Process.h"

template<>
Node<Process*>* PriorityQueue<Process*>::getNodeBefore(Process* entry) const
{
    Node<Process*>* prevPtr = nullptr;
    Node<Process*>* currPtr = head;
    while (currPtr != nullptr && *entry > *(currPtr->getData()))
    {
        prevPtr = currPtr;
        currPtr = currPtr->getNext();
    }

    return prevPtr;
}

template<>
void PriorityQueue<Process*>::print() const
{
    Node <Process*>* trav = head;
    while (trav != nullptr)
    {
        std::cout << trav->getData()->getID();
        if (trav->getNext())
            std::cout << ", ";
        trav = trav->getNext();
    }
}