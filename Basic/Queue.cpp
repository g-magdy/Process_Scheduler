#include "Queue.h"
#include "../Components/Process.h"
#include <iostream>
using namespace std;

template<>
void Queue<Process*>::print() const
{
	if (isEmpty())
		return;

	Node<Process*>* cur = front;
	while (cur)
	{
		cout << *(cur->getData());
		cur = cur->getNext();
		if(cur)
			cout << ", ";
	}
}