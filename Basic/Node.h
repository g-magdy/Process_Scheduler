#pragma once

template <class ItemType>
class Node
{
	ItemType data;
	Node<ItemType>* next;
public:
	Node();
	Node(const ItemType& entry);
	void setData(const ItemType& entry);
	void setNext(Node<ItemType>* ptr);
	ItemType getData() const;
	Node<ItemType>* getNext() const;
};

template<class ItemType>
inline Node<ItemType>::Node() : next(nullptr)
{
}

template<class ItemType>
inline Node<ItemType>::Node(const ItemType& entry) : data(entry)
{
}

template<class ItemType>
inline void Node<ItemType>::setData(const ItemType& entry)
{
	data = entry;
}

template<class ItemType>
inline void Node<ItemType>::setNext(Node<ItemType>* ptr)
{
	next = ptr;
	// this is a comment
}

template<class ItemType>
inline ItemType Node<ItemType>::getData() const
{
	return data;
}

template<class ItemType>
inline Node<ItemType>* Node<ItemType>::getNext() const
{
	return next;
}
