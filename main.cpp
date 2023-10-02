#include"Scheduler.h"

int main()
{
	Scheduler ProScheduler;

	if (ProScheduler.startUp())
		ProScheduler.run();

	system("pause");
	return 0;
}
