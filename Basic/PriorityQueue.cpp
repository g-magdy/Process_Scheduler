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
void PriorityQueue<Process*>::push(Process* entry)
{
    Node<Process*>* prevPtr = getNodeBefore(entry);
    Node<Process*>* newNodePtr = new Node<Process*>(entry);
    if (isEmpty() || prevPtr == nullptr) // luckily: entry is the new lowest element or the only one
    {
        newNodePtr->setNext(head);
        head = newNodePtr;
    }
    else
    {
        newNodePtr->setNext(prevPtr->getNext());
        prevPtr->setNext(newNodePtr);
    }
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