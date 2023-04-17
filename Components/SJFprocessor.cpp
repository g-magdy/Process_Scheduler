#include "SJFprocessor.h"

SJF::SJF(Scheduler* pscheduler):Processor(pscheduler, SJF_T)
{
}

void SJF::scheduleAlgo(int currentTimeStep)
{
	Processor::scheduleAlgo(currentTimeStep);
}

void SJF::pullFromRDY(Process*& p)
{
	RDY.pop(p);
}

void SJF::pushToRDY(Process* p)
{
	p->setProcessState(READY);
	p->setHandlingCPU(SJF_T);
	RDY.push(p);
}