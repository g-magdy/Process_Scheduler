#include"Scheduler.h"

int main()
{
	Scheduler ProScheduler;

	if (ProScheduler.startUp())
		ProScheduler.run();

	return 0;
}
