#include "RRprocessor.h"
#include "../Scheduler.h"

RRprocessor::RRprocessor(Scheduler* pscheduler, std::string s, int tslice, int rtf) :Processor(pscheduler, RR_T, s),timeSlice(tslice), RTF(rtf)
{
}

void RRprocessor::scheduleAlgo(int currentTimeStep)
{
	Process* pRun = nullptr;				// A pointer to the running process

	if (getCPUstate() == IDLE)				// if the cpu is idle, check if there is any process in the ready list
	{
		if (pullFromRDY(pRun))				// if ther, get it and put in run
		{
			setRunningProcess(pRun);
			pRun->setProcessState(RUN);
			updateCPUstate();
		}
	}
	
	updateCPUTs();

	if (getCPUstate() == Busy)
	{
		pRun = getRunningProcess();
		pRun->setResponseT(currentTimeStep);			// sets the response time if this is the first time the process is handled
		pRun->updateFinishedCPUT();						//increament the CPU time of this process by one

		//check for IO requests
		Pair<int, int> nextRequest;
		if (pRun->peekNextIOR(nextRequest))
		{
			if (nextRequest.first == (pRun->getFinishedCPUT()))
			{
				pScheduler->moveToBLK(pRun);
				pRun == nullptr;
			}
		}

		//check for termination
		if (pRun && (pRun->getCPUT() - pRun->getFinishedCPUT() == 0))
		{
			pScheduler->moveToTRM(pRun);
			pRun == nullptr;
		}

		//chek for the time slice if it has ended or not
		if (totalBusyT % timeSlice == 0)
			if (pRun)
			{
				/// TODO: Process migration is handled in this part
				movetoMyRDY(); //update cpu state is done inside this funciton
			}
	}
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



