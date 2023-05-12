#include "FCFSprocessor.h"
#include "../Scheduler.h"

FCFSprocessor::FCFSprocessor(Scheduler* pscheduler, std::string s, int maxw, int forkP):Processor(pscheduler, FCFS_T, s) ,MaxW(maxw), forkProbability(forkP)
{
}

void FCFSprocessor::scheduleAlgo(int currentTimeStep)
{
	if (!runningProcess) // was not running any process
	{
		// more than one process can migrate
		// I'll stop when i find a suitable one to run
		while (pullFromRDY(runningProcess)) // if the ready list is not empty
		{
			int wait = pScheduler->getTimeStep() - runningProcess->getArrivalT() - runningProcess->getFinishedCPUT(); 
			/// TODO: runningProcess->setWaitingTime(wait);
			
			if (wait > MaxW && runningProcess->getMyParent() == nullptr)
				pScheduler->migrate(runningProcess, RR_T);
			else
				break;
		}
		if (runningProcess) // ensure that i have pulled a vaild process : thanks Ahmed :)
		{
			runningProcess->setProcessState(RUN);
			runningProcess->setResponseT(currentTimeStep - runningProcess->getArrivalT());
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
	else // no running process and empty Ready list
	{
		setCPUstate(IDLE);
		totalIdleT++;
	}
  
	// forking 
	int randN=pScheduler->random();
	// a process can fork only once so i need to make sure that it has NO child before calling fork() (i addded a '!')
	if (runningProcess && (!runningProcess->getMyChild() && randN <= forkProbability))
		fork();

  updateCPUstate();
}


bool FCFSprocessor::pullFromRDY(Process* & p)
{
	if (!RDY.isEmpty())
	{
		RDY.pop_front(p);
		expectedFinishT -= p->getCPUT() - p->getFinishedCPUT();
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

void FCFSprocessor::pushTopOfRDY(Process*& p)
{
	expectedFinishT += p->getCPUT() - p->getFinishedCPUT();
	p->setProcessState(READY);
	p->setHandlingCPU(FCFS_T);
	RDY.push_front(p);

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

void FCFSprocessor::fork()
{
	if (runningProcess)
	{
		int  ct;
		ct = runningProcess->getCPUT() - runningProcess->getFinishedCPUT();
		Process* child = pScheduler->createChild(ct, runningProcess);
		runningProcess->setMyChild(child);

	}
	
}

