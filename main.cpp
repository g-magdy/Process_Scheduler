
#include"Scheduler.h"

int main()
{

	Scheduler* ProScheduler = new Scheduler();

	ProScheduler->simulation();

	delete ProScheduler;

	return 0;
}
