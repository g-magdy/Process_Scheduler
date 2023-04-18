#include "RRprocessor.h"

RRprocessor::RRprocessor(Scheduler* pscheduler, std::string s, int tslice, int rtf) :Processor(pscheduler, RR_T, s),timeSlice(tslice), RTF(rtf)
{
}

void RRprocessor::scheduleAlgo(int currentTimeStep)
{
	Processor::scheduleAlgo(currentTimeStep);
}


bool RRprocessor::pullFromRDY(Process*& p)
{
	if (!RDY.isEmpty())
	{
		RDY.pop(p);
		return true;
	}
	return false;
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



