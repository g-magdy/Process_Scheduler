#include "FCFSprocessor.h"
#include "../Scheduler.h"

FCFSprocessor::FCFSprocessor(Scheduler* pscheduler, int maxw, int forkP):Processor(pscheduler, FCFS_T) ,MaxW(maxw), forkProbability(forkP)
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

bool FCFSprocessor::kill(std::string idtoKill)
{
	if (RDY.find(idtoKill))
	{
		Process * ptr=RDY.removeByID(idtoKill);
		pScheduler->moveToTRM(ptr);
		return 1;
	}
	return 0;
}

bool FCFSprocessor::fork()
{
	return false;
}

