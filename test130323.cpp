#include "Basic/List.h" // Note that I ned to specify the path
// iostream is already included in List.h 
#include "Basic/Queue.h"
#include "Basic/stack.h"
#include "Basic/PriorityQueue.h"
#include "Components/Process.h"

using namespace std;

void List_test(List<string>* listPtr)
{
	string items[] = { "one", "two", "three", "four", "five", "six" };

	for (int i = 0; i < 6; i++)
	{
		listPtr->push_back(items[i]);
	}
	cout << "Found one ? (should be 1)" << listPtr->find("one") << endl;
	cout << "Found three ? (should be 1)" << listPtr->find("three") << endl;
	cout << "Found six ? (should be 1)" << listPtr->find("six") << endl;
	listPtr->pop_back();
	listPtr->pop_front();
	cout << " after removing front and back :: \n";
	cout << "Found one ? (should be 0)" << listPtr->find("one") << endl;
	cout << "Found six ? (should be 0)" << listPtr->find("six") << endl;
}

template<typename T>
void print(T* ob)
{
	std::cout << *ob;
}

int main()
{
	Process* p = new Process("83", 8, 12);
	Process* n = new Process("34", 8, 12);
	Process* r = new Process("21", 8, 12);

	Queue<Process*> myq;
	myq.push(p);
	myq.push(n);
	myq.push(r);
	myq.print();
	std::cout << "\nTest list : \n";
	List<Process*>mylist;

	mylist.push_back(p);
	mylist.push_back(n);
	mylist.push_back(r);
	mylist.print();

	List<int> l2;
	l2.push_back(10);
	l2.push_back(20);
	l2.push_back(30);
	l2.print();

	List<string> * l3 = new List<string>;
	List_test(l3);

	return 0;
}