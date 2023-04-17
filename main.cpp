
#include"Components/Scheduler.h"

int main()
{

	Scheduler *ProScheduler=new Scheduler ;

	ProScheduler->startUP();

	while( ProSheduler->run() );

	return 0;
}
