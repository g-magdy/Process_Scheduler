#include "SJFprocessor.h"

SJF::SJF(Scheduler* pscheduler, std::string s):Processor(pscheduler, SJF_T, s)
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

void SJF::printRDYList()
{
	std::cout << RDY.size() << " RDY: ";
	RDY.print();
}
