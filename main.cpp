
#include"Scheduler.h"

int main()
{

	Scheduler* ProScheduler= new Scheduler();

	ProScheduler->startUp();

	while(ProScheduler->run());

	return 0;
}
