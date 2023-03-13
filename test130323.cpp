#include "Basic/LinkedList.h" // Note that I ned to specify the path
// iostream is already included in LinkedList.h 

int main()
{
	LinkedList<int> mylist;
	for (int i = 0; i < 5; i++)
	{
		mylist.insertEnd(6 * i);
	}
	mylist.printlist();
	return 0;
}