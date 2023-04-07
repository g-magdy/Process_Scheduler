#include "Basic/LinkedList.h" // Note that I ned to specify the path
// iostream is already included in LinkedList.h 
#include "Basic/Queue.h"
#include "Basic/stack.h"
#include "Basic/PriorityQueue.h"

using namespace std;
int main()
{
	PriorityQueue<float> p;
	p.add(4);
	p.add(3);
	p.add(2);
	p.add(5);
	p.add(3.5);

	
	cout << p.peek() << endl;
	p.show();
	p.remove();
	p.remove();
	p.show();
	cout << boolalpha << p.isEmpty() << endl;
	while (p.remove());
	cout << boolalpha << p.isEmpty() << endl;
	p.show();
	p.add(92);
	p.add(30);
	p.add(45);
	p.add(60);
	p.show();

	return 0;
}