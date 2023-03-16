#include "Basic/LinkedList.h" // Note that I ned to specify the path
// iostream is already included in LinkedList.h 
#include "Basic/Queue.h"
#include"Basic/stack.h"

using namespace std;
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
	/// <summary>
	/// test stack
	/// </summary>
	/// <returns></returns>
	stack<int> s1(11);
	stack<float>s2(10);

	stack<float>s4;
	s1.push(15);
	s1.push(15);
	s1.push(15);
	s1.push(15);
	s1.push(16);
	s1.print();
	cout << endl;
	stack<int>s3(s1);
	s3.print();
	cout << endl;
	cout << s3.size();
	return 0;
}