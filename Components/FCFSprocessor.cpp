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
			totalIdleT++;
		}
	}
	
	if(runningProcess) // currently executing or pulled fresh from ready in line 12
	{
		setCPUstate(Busy); // not sure if needed
		runningProcess->updateFinishedCPUT();
		expectedFinishT--;
		totalBusyT++;

		// IO check
		Pair<int, int> req;
		if (runningProcess->peekNextIOR(req)) // if exists
		{
			if (req.first == runningProcess->getFinishedCPUT()) //right time
			{
				// remove the remaining time to finish the process execution from the CPU's expected finsih time
				expectedFinishT -= (runningProcess->getCPUT() - runningProcess->getFinishedCPUT());
				pScheduler->moveToBLK(runningProcess);
				runningProcess = nullptr;
			}
		}
		// Termination check
		if (runningProcess && runningProcess->getFinishedCPUT() == runningProcess->getCPUT())
		{
			pScheduler->moveToTRM(runningProcess); // modified
			runningProcess = nullptr;
		}
	}

	updateCPUstate();

	///TODO: migration, forking
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
	// add the remaining time of exectution of this process to the expected finsih time of the CPU
	expectedFinishT += p->getCPUT() - p->getFinishedCPUT();
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
	//chech if the running process is the one to kill
	if (runningProcess)
	{
		if (runningProcess->getID() == idtoKill)
		{
			pScheduler->moveToTRM(runningProcess);
			runningProcess = nullptr;

			//update the state of the CPU
			if (RDY.isEmpty())
				setCPUstate(IDLE);
			else
				setCPUstate(Busy);

			//if found return ture
			return true;
		}
		//else search in the RDY list
	}
	
	if(RDY.isEmpty() == false)
	{	
		//search the RDY list for the Process to kill
		//to do so we need a temp process with the id we are looking for
		Process processToKill(idtoKill);
		int indx = RDY.find(&processToKill);
		//will enter the if statement if the process was found
		if (indx != -1)
		{
			Process* ptr = RDY.remove(indx);
			pScheduler->moveToTRM(ptr);
			return true;
		}
	}

	return false;
}

bool FCFSprocessor::fork()
{
	return false;
}

