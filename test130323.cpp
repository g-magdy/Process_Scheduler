#include "Basic/LinkedList.h" // Note that I ned to specify the path
// iostream is already included in LinkedList.h 
#include "Basic/Queue.h"
#include "Basic/stack.h"
#include "Basic/PriorityQueue.h"
#include "Components/Process.h"

template<typename T>
void print(T* ob)
{
	std::cout << *ob;
}

using namespace std;
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