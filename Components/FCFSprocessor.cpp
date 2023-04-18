#include "FCFSprocessor.h"
#include "../Scheduler.h"

FCFSprocessor::FCFSprocessor(Scheduler* pscheduler, std::string s, int maxw, int forkP):Processor(pscheduler, FCFS_T, s) ,MaxW(maxw), forkProbability(forkP)
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

void FCFSprocessor::printRDYList()
{
	std::cout << RDY.getCount() << " RDY: ";
	RDY.print();
}

bool FCFSprocessor::kill(std::string idtoKill)
{
	Process processToKill(idtoKill);
	int indx = RDY.find(&processToKill);
	if (indx != -1)
	{
		Process * ptr = RDY.remove(indx);
		pScheduler->moveToTRM(ptr);
		return 1;
	}
	return 0;
}

bool FCFSprocessor::fork()
{
	return false;
}

