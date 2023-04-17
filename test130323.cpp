/*#include "Basic/List.h" // Note that I ned to specify the path
// iostream is already included in List.h 
#include "Basic/Queue.h"
#include "Basic/stack.h"
#include "Basic/PriorityQueue.h"
#include "Components/Process.h"

using namespace std;

void List_test(List<Process*>& mylist)
{
	Process* p = new Process("83", 8, 12);
	Process* n = new Process("34", 8, 12);
	Process* r = new Process("21", 8, 12);
	Process* s = new Process("93", 8, 12);
	Process* m = new Process("143", 8, 12);

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
}
void test_priorityQ(PriorityQueue<Process*> pq)
{
	cout << "\nTesting the PriorityQueue.\n";
	Process* p = new Process("83", 8, 12);
	Process* n = new Process("34", 8, 5);
	Process* r = new Process("21", 8, 1);
	Process* s = new Process("93", 8, 46);
	Process* m = new Process("143", 8, 34);

	pq.push(p);
	pq.push(n);
	pq.push(r);
	pq.push(s);
	pq.push(m);
	pq.print();
	Process* poped;
	pq.pop(poped);
	cout << endl << poped->getID() << endl;
	pq.print();
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
	Process* del = nullptr;
	del = listPtr->removeByID(p->getID());
	cout << del->getID() << "removed\n";
	del = listPtr->removeByID(r->getID());
	cout << del->getID() << "removed\n";
	del = listPtr->removeByID(m->getID());
	cout << del->getID() << "removed\n";
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
	List<Process*>mylist;
	List_test(mylist); //testing all the functions of the list

	List<string>* listPtr1 = new List<string>;
	removeTest1(listPtr1); //tests remove by index

	List<Process*>* listPtr2 = new List<Process*>;
	//removeTest2(listPtr2); //tests remove by ID in the list ADT
	
	PriorityQueue<Process*> list3;
	test_priorityQ(list3);

	return 0;
}
*/