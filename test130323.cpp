#include "Basic/List.h" // Note that I ned to specify the path
// iostream is already included in List.h 
#include "Basic/Queue.h"
#include "Basic/stack.h"
#include "Basic/PriorityQueue.h"
#include "Components/Process.h"

using namespace std;

void List_test(List<string>* listPtr)
{
	cout << "Is empty : " << listPtr->isEmpty() << " (should be 1)\n";
	cout << "Count : " << listPtr->getCount() << " (should be 0)\n\n";

	cout << "testing insertEnd\n";
	string items[] = { "one", "two", "three", "four", "five", "six" };

	for (int i = 0; i < 6; i++)
	{
		listPtr->insertEnd(items[i]);
	}
	cout << "Printing list :: ";
	listPtr->print();
	cout << "should be one .. .. six\n";

	cout << "Is empty : " << listPtr->isEmpty() << " (should be 0)\n";
	cout << "Count : " << listPtr->getCount() << " (should be 6)\n\n";

	cout << "clearing list ::\n";
	listPtr->clear();

	cout << "Is empty : " << listPtr->isEmpty() << " (should be 1)\n";
	cout << "Count : " << listPtr->getCount() << " (should be 0)\n\n";

	cout << "testing begin and end\n";
	for (int i = 0; i < 3; i++)
	{
		listPtr->insertBegin(items[i]);
		listPtr->insertEnd(items[i]);
	}
	cout << "Printing list :: ";
	listPtr->print();
	cout << "should be 3 2 1 1 2 3 (in letters)\n";	
}

int main()
{
	List<string>* mylist;
	mylist = new List<string>();
	List_test(mylist);
	return 0;
}