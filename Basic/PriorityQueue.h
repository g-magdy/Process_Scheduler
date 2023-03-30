#pragma once
#include "Node.h"
#include "PriorityQueueInterface.h"
template <class ItemType>
class PriorityQueue : public PriorityQueueInterface<ItemType>
{
private:
    // we don't need tail
    // we only remove from the front (highest priority)
    // we don't always add at the end of the list
    Node<ItemType>* head;   
    Node<ItemType>* copychain(Node<ItemType>* originalChainPtr);
public:
    PriorityQueue();
    PriorityQueue(const PriorityQueue<ItemType>& original);
    bool isEmpty() const;
};

template<class ItemType>
// recursive function to be used in the copy constructor
inline Node<ItemType>* PriorityQueue<ItemType>::copychain(Node<ItemType>* originalChainPtr)
{
    Node<ItemType>* copiedChainPtr;
    if (originalChainPtr == nullptr)
    {
        copiedChainPtr = nullptr;
    }
    else
    {
        copiedChainPtr = new Node<ItemType>(originalChainPtr->getData());
        copiedChainPtr->setNext(copychain(originalChainPtr->getNext()));
    }

    return copiedChainPtr;
}

template<class ItemType>
inline PriorityQueue<ItemType>::PriorityQueue() : head(nullptr)
{
}

template<class ItemType>
inline PriorityQueue<ItemType>::PriorityQueue(const PriorityQueue<ItemType>& original)
{
    head = copychain(original.head);
}

template<class ItemType>
inline bool PriorityQueue<ItemType>::isEmpty() const
{
    return (head == nullptr);
}
