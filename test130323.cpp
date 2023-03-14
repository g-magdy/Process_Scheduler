#include "Basic/LinkedList.h" // Note that I ned to specify the path
// iostream is already included in LinkedList.h 
#include "Basic/Queue.h"

int main()
{
	LinkedList<int> mylist;
	for (int i = 0; i < 5; i++)
	{
		mylist.insertEnd(6 * i);
	}
	mylist.printlist();

	Queue<int> myqueue;
	for (int i = 0; i < 5; i++)
	{
		myqueue.push(7 * i);
	}
	myqueue.print();
	return 0;
}