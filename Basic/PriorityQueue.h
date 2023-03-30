#pragma once

#include <iostream> /// (will be removed) only for using std::cout to print queue 

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
    
    // recursive function to be used in the copy constructor
    Node<ItemType>* copychain(Node<ItemType>* originalChainPtr);
    
    // iteratively loops through the sorted list till if finds the element greater than the given one
    // returns pointer to the node before it
    Node<ItemType>* getNodeBefore(const ItemType& entry) const;
public:
    PriorityQueue();
    PriorityQueue(const PriorityQueue<ItemType>& original);
    bool isEmpty() const;
    void add(const ItemType& entry);
    bool remove();
    ItemType peek() const;
    void show() const; /// Only for testing
    ~PriorityQueue();
};

template<class ItemType>
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
inline Node<ItemType>* PriorityQueue<ItemType>::getNodeBefore(const ItemType& entry) const
{
    Node<ItemType>* prevPtr = nullptr;
    Node<ItemType>* currPtr = head;
    while (currPtr != nullptr && entry > currPtr->getData())
    {
        prevPtr = currPtr;
        currPtr = currPtr->getNext();
    }

    return prevPtr;
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

template<class ItemType>
inline void PriorityQueue<ItemType>::add(const ItemType& entry)
{
    Node<ItemType>* prevPtr = getNodeBefore(entry);
    Node<ItemType>* newNodePtr = new Node<ItemType>(entry);
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

template<class ItemType>
inline bool PriorityQueue<ItemType>::remove()
{
    if (isEmpty())
        return false;
    else
    {
        Node<ItemType>* toDeletePtr = head;
        head = head->getNext();
        delete toDeletePtr;
        return true;
    }
}

template<class ItemType>
inline ItemType PriorityQueue<ItemType>::peek() const
{
    return head->getData(); /// TODO : Unhandled exception ! if the queue is empty
}

template<class ItemType>
inline void PriorityQueue<ItemType>::show() const
{
    Node <ItemType>* trav = head;
    while (trav != nullptr)
    {
        std::cout << trav->getData() << " -> ";
        trav = trav->getNext();
    }
    std::cout << "NULL\n";
}

template<class ItemType>
inline PriorityQueue<ItemType>::~PriorityQueue()
{
    while (!isEmpty())
        remove();
}
