#include "RRprocessor.h"

RRprocessor::RRprocessor(Scheduler* pscheduler,int tslice, int rtf) :Processor(pscheduler, RR_T),timeSlice(tslice), RTF(rtf)
{
}

void RRprocessor::scheduleAlgo(int currentTimeStep)
{
	Processor::scheduleAlgo(currentTimeStep);
}


void RRprocessor::pullFromRDY(Process*& p)
{
	RDY.pop(p);
}

void RRprocessor::pushToRDY(Process* p)
{
	p->setProcessState(READY);
	p->setHandlingCPU(RR_T);
	RDY.push(p);
}

void RRprocessor::printRDYList()
{
	std::cout << RDY.size() << " RDY: ";
	RDY.print();
}



