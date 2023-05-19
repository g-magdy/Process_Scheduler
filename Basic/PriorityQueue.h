#pragma once
#include <iostream> 
#include "Node.h"
class Process;

template <class ItemType>
class PriorityQueue
{
private:
    // we don't need tail
    // we only remove from the front (highest priority)
    // we don't always add at the end of the list
    Node<ItemType>* head;
    int count;
    
    // recursive function to be used in the copy constructor
    Node<ItemType>* copychain(Node<ItemType>* originalChainPtr);
    
    // iteratively loops through the sorted list till if finds the element greater than the given one
    // returns pointer to the node before it
    Node<ItemType>* getNodeBefore(ItemType entry) const;
public:
    PriorityQueue();                                            //defult argument constructor
    PriorityQueue(const PriorityQueue<ItemType>& original);     //copy constructor
    bool isEmpty() const;                                       //checks whether the queue is empty or not
    void push(ItemType entry);                                  //adds an element in its right position in the queue
    bool pop();                                                 //pop the front element of the queue
    bool pop(ItemType&);
    ItemType peek() const;                                      //gives a glance to the front element of the queue
    int size() const;                                           // returns the number of elements in the PriorityQueue
    void print() const;                                         //prints all the elements of the queue
    ~PriorityQueue();                                           //destructor
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
inline Node<ItemType>* PriorityQueue<ItemType>::getNodeBefore(ItemType entry) const
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
inline PriorityQueue<ItemType>::PriorityQueue() : head(nullptr), count(0)
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
inline void PriorityQueue<ItemType>::push(ItemType entry)
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
    count++;
}

template<class ItemType>
inline bool PriorityQueue<ItemType>::pop()
{
    if (isEmpty())
        return false;
    else
    {
        Node<ItemType>* toDeletePtr = head;
        head = head->getNext();
        delete toDeletePtr;
        count--;
        return true;
    }
}

template<class ItemType>
inline bool PriorityQueue<ItemType>::pop(ItemType& poped)
{
    if (isEmpty())
        return false;
    else
    {
        poped = head->getData();
        Node<ItemType>* toDeletePtr = head;
        head = head->getNext();
        delete toDeletePtr;
        count--;
        return true;
    }
}

template<class ItemType>
inline ItemType PriorityQueue<ItemType>::peek() const
{
    if (isEmpty())
        throw "empty";
    return head->getData();
}

template<class ItemType>
inline int PriorityQueue<ItemType>::size() const
{
    return count;
}


template<class ItemType>
inline PriorityQueue<ItemType>::~PriorityQueue()
{
    while (!isEmpty())
        pop();
}

template<>
void PriorityQueue<Process*>::print() const;
template<>
Node<Process*>* PriorityQueue<Process*>::getNodeBefore(Process* entry) const;