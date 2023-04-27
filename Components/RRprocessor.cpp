#include "RRprocessor.h"
#include "../Scheduler.h"

RRprocessor::RRprocessor(Scheduler* pscheduler, std::string s, int tslice, int rtf) :Processor(pscheduler, RR_T, s),timeSlice(tslice), RTF(rtf)
{
}

void RRprocessor::scheduleAlgo(int currentTimeStep)
{
	if (!runningProcess)				// if the cpu is idle, check if there is any process in the ready list
	{
		if (pullFromRDY(runningProcess))				// if ther, get it and put in run
		{
			runningProcess->setProcessState(RUN);
		}
	}
	

	if (runningProcess)
	{
		runningProcess->setResponseT(currentTimeStep - runningProcess->getArrivalT());			// sets the response time if this is the first time the process is handled
		runningProcess->updateFinishedCPUT();						//increament the CPU time of this process by one
		expectedFinishT--;

		//check for IO requests
		Pair<int, int> nextRequest;
		if (runningProcess->peekNextIOR(nextRequest))
		{
			if (nextRequest.first == (runningProcess->getFinishedCPUT()))
			{
				expectedFinishT -= (runningProcess->getCPUT() - runningProcess->getFinishedCPUT());
				pScheduler->moveToBLK(runningProcess);
				runningProcess == nullptr;
			}
		}

		//check for termination
		if (runningProcess && (runningProcess->getCPUT() == runningProcess->getFinishedCPUT()))
		{
			pScheduler->moveToTRM(runningProcess);
			runningProcess == nullptr;
		}

		//chek for the time slice if it has ended or not
		if (totalBusyT % timeSlice == 0)
			if (runningProcess)
			{
				/// TODO: Process migration is handled in this part
				pushToRDY(runningProcess);
				runningProcess = nullptr;
			}

		totalBusyT++;
	}
	else {
		totalIdleT++;
	}
	
	updateCPUstate();
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
	expectedFinishT += p->getCPUT() - p->getFinishedCPUT();
	p->setProcessState(READY);
	p->setHandlingCPU(RR_T);
	RDY.push(p);
}

void RRprocessor::printRDYList()
{
	std::cout << RDY.size() << " RDY: ";
	RDY.print();
}



