#include "Basic/List.h" // Note that I ned to specify the path
// iostream is already included in List.h 
#include "Basic/Queue.h"
#include "Basic/stack.h"
#include "Basic/PriorityQueue.h"
#include "Components/Process.h"

using namespace std;

void List_test(List<char>* listPtr)
{
	char items[] = { 'a', 'b', 'c', 'd', 'e', 'f'};

	for (int i = 0; i < 6; i++)
	{
		listPtr->push_back(items[i]);
	}
	cout << "Found a ? (should be 1)" << listPtr->find('a') << endl;
	cout << "Found c ? (should be 1)" << listPtr->find('c') << endl;
	cout << "Found f ? (should be 1)" << listPtr->find('f') << endl;
	listPtr->pop_back();
	listPtr->pop_front();
	cout << " after removing front and back :: \n";
	cout << "Found one ? (should be 0)" << listPtr->find('a') << endl;
	cout << "Found six ? (should be 0)" << listPtr->find('f') << endl;
}

template<typename T>
void print(T* ob)
{
	cout << *ob;
}

int main()
{
	Process* p = new Process("83", 8, 12);
	Process* n = new Process("34", 8, 12);
	Process* r = new Process("21", 8, 12);
	Process* s = new Process("93", 8, 12);
	Process* m = new Process("143", 8, 12);
	List<Process*>mylist;

	mylist.push_front(n);
	mylist.push_front(p);
	mylist.push_back(r);
	mylist.push_back(s);
	mylist.push_back(m);
	mylist.print(); // 83,34, 21, 93, 143
	cout << endl;
	cout << boolalpha << mylist.find("24") << endl; //false
	cout << boolalpha << mylist.find("93") << endl; //true
	mylist.pop_back();
	mylist.pop_front();
	mylist.print(); //34, 21, 93
	Process* temp;
	mylist.pop_front(temp);
	cout << endl;
	cout << temp->getID() << endl; // 34
	cout << mylist.getCount() << endl; //2
	mylist.print(); //21, 93

	return 0;
}