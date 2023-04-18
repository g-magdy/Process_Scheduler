
#include"Scheduler.h"

int main()
{

	Scheduler* ProScheduler= new Scheduler();

	ProScheduler->startUp();

	ProScheduler->run();

	return 0;
}
