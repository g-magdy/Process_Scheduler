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

void removeTest1(List<string>* listPtr)
{
	cout << "\n//////////////////\n";
	cout << "Normal Items : ";
	listPtr->push_back("Tom");
	listPtr->push_back("Jerry");
	listPtr->push_back("Donald");
	listPtr->push_back("Duck");
	cout <<  "\n" << listPtr->getCount() << endl;
	listPtr->print();
	listPtr->removeByIndex(2); /// removed "Jerry"
	listPtr->removeByIndex(0);
	listPtr->removeByIndex(10);
	listPtr->removeByIndex(3); /// removed "Duck"
	listPtr->removeByIndex(2); /// removed "Donald"
	cout << "\n" << listPtr->getCount() << endl;
	listPtr->print();
	cout << "\n//////////////////\n";
}
void removeTest2(List<Process*>* listPtr)
{
	cout << "\n//////////////////\n";
	cout << "Process ptrs: \n";
	listPtr->clear(); /// Start with empty
	Process* p = new Process("83", 8, 12);
	Process* n = new Process("34", 8, 12);
	Process* r = new Process("21", 8, 12);
	Process* s = new Process("93", 8, 12);
	Process* m = new Process("143", 8, 12);
	listPtr->push_back(p);
	listPtr->push_back(n);
	listPtr->push_back(r);
	listPtr->push_back(s);
	listPtr->push_back(m);
	cout << "count :" << listPtr->getCount()<<'\n';
	listPtr->print();

	cout << "\n\nafter removing 83, 21, 143 : \n";
	listPtr->removeByID(p->getID());
	listPtr->removeByID(r->getID());
	listPtr->removeByID(m->getID());
	cout << "count :" << listPtr->getCount()<<'\n';
	listPtr->print();
	cout << "\n//////////////////\n";
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

	List<string>* listPtr1 = new List<string>;
	List<Process*>* listPtr2 = new List<Process*>;
	//removeTest1(listPtr);
	removeTest2(listPtr2);
	return 0;
}