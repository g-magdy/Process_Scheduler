#include "Basic/LinkedList.h" // Note that I ned to specify the path
// iostream is already included in LinkedList.h 
#include "Basic/Queue.h"
#include "Basic/stack.h"
#include "Basic/PriorityQueue.h"
#include "Components/Process.h"

using namespace std;
int main()
{
	Process *p = new Process("65", 5, 7);

	cout << *p;

	return 0;
}