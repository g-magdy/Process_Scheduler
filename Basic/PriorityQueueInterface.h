#pragma once

template <class ItemType>
class PriorityQueueInterface
{
    // returns true if there are no entries in the queue
    virtual bool isEmpty() const = 0;

    // inserts it such that the queue is in ascending order
    virtual void add(const ItemType& entry) = 0;

    // deletes the entry with the highest priority (lowest value)
    virtual bool remove() = 0;

    // please DO NOT call this function if the queue is empty
    // (until we handle this exception)
    // it returns the element with highest priority (lowest value)
    // without removing it 
    virtual ItemType peek() const = 0;
};