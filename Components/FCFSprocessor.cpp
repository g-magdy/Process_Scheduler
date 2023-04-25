#include "FCFSprocessor.h"
#include "../Scheduler.h"

FCFSprocessor::FCFSprocessor(Scheduler* pscheduler, std::string s, int maxw, int forkP):Processor(pscheduler, FCFS_T, s) ,MaxW(maxw), forkProbability(forkP)
{
}

void FCFSprocessor::scheduleAlgo(int currentTimeStep)
{
	if (!runningProcess) // was not running any process
	{
		if (pullFromRDY(runningProcess)) // if the ready list is not empty
		{
			runningProcess->setProcessState(RUN);
			//runningProcess->setHandlingCPU(FCFS_T);  (set only when adding to ready list)
			runningProcess->setResponseT(currentTimeStep - runningProcess->getArrivalT());
			//runningProcess->updateFinishedCPUT(); (updated only on line 28)
		}
		else // no running process and empty Ready list
		{
			setCPUstate(IDLE);
		}
	}
	
	if(runningProcess) // currently executing or pulled fresh from ready in line 12
	{
		setCPUstate(Busy); // not sure if needed
		runningProcess->updateFinishedCPUT();

		// IO check
		Pair<int, int> req;
		if (runningProcess->peekNextIOR(req)) // if exists
		{
			if (req.first == runningProcess->getFinishedCPUT()) //right time
			{
				pScheduler->moveToBLK(runningProcess);
				runningProcess = nullptr;
			}
		}
		// Termination check
		else if (runningProcess->getFinishedCPUT() == runningProcess->getCPUT())
		{
			pScheduler->moveToTRM(runningProcess); // modified
			runningProcess = nullptr;
		}
	}
	///TODO: migration, forking
	updateCPUTs();
}


bool FCFSprocessor::pullFromRDY(Process* & p)
{
	if (!RDY.isEmpty())
	{
		RDY.pop_front(p);
		return true;
	}
	return false;
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
		/// TODO: what if the killed process was the running process ?
		/*
		if (ptr->getProcessState() == RUN)
		{
			runningProcess = nullptr;
		}
		*/
		pScheduler->moveToTRM(ptr);
		return 1;
	}
	return 0;
}

bool FCFSprocessor::fork()
{
	return false;
}

