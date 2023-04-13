#include "Basic/List.h" // Note that I ned to specify the path
// iostream is already included in List.h 
#include "Basic/Queue.h"
#include "Basic/stack.h"
#include "Basic/PriorityQueue.h"
#include "Components/Process.h"

//using namespace std;
//
//void List_test(List<string>* listPtr)
//{
//	string items[] = { "one", "two", "three", "four", "five", "six" };
//
//	for (int i = 0; i < 6; i++)
//	{
//		listPtr->push_back(items[i]);
//	}
//
//
//	cout << "printing then clearing list using remove front while it is not emty ::\n";
//	while (!listPtr->isEmpty())
//	{
//		cout << listPtr->front() << " ";
//		listPtr->pop_front();
//	}
//	cout << "\nIs empty : " << listPtr->isEmpty() << " (should be 1)\n";
//	cout << "Count : " << listPtr->getCount() << " (should be 0)\n\n";
//
//	cout << "New data ..\n";
//	for (int i = 0; i < 3; i++)
//	{
//		listPtr->push_front(items[i]);
//		listPtr->push_back(items[i]);
//	}
//	cout << "Is empty : " << listPtr->isEmpty() << " (should be 0)\n";
//	cout << "Count : " << listPtr->getCount() << " (should be 6)\n\n";
//
//	cout << "clearing list using remove last while it is not emty ::\n";
//	while (!listPtr->isEmpty())
//	{
//		listPtr->pop_back();
//	}
//	cout << "Is empty : " << listPtr->isEmpty() << " (should be 1)\n";
//	cout << "Count : " << listPtr->getCount() << " (should be 0)\n\n";
//}
//
//template<typename T>
//void print(T* ob)
//{
//	std::cout << *ob;
//}

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

	return 0;
}