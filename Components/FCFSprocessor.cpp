#include "FCFSprocessor.h"
#include "Scheduler.h"

FCFSprocessor::FCFSprocessor(Scheduler* pscheduler):Processor(pscheduler, FCFS_T)
{
}

void FCFSprocessor::scheduleAlgo(int currentTimeStep)
{
	Processor::scheduleAlgo(currentTimeStep);
}


void FCFSprocessor::pullFromRDY(Process* & p)
{
	RDY.pop_front(p);								
}

void FCFSprocessor::pushToRDY(Process* p)
{
	p->setProcessState(READY);
	p->setHandlingCPU(FCFS_T);
	RDY.push_back(p);
}

