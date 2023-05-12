#include "SJFprocessor.h"
#include"../Scheduler.h"
SJF::SJF(Scheduler* pscheduler, std::string s):Processor(pscheduler, SJF_T, s)
{
}

void SJF::scheduleAlgo(int currentTimeStep)
{
	if (!runningProcess) {

		if (pullFromRDY(runningProcess)) {
			// sets the response time if this is the first time the process is handled
			runningProcess->setProcessState(RUN);
			runningProcess->setResponseT(currentTimeStep - runningProcess->getArrivalT());
		}
		else {
			totalIdleT++;
		}

	}
	if (runningProcess)
	{
		totalBusyT++;
		runningProcess->updateFinishedCPUT();
		expectedFinishT--;

		Pair<int, int> p;
		if (runningProcess->peekNextIOR(p)) {

			if (p.first == runningProcess->getFinishedCPUT())
			{
				expectedFinishT -= (runningProcess->getCPUT() - runningProcess->getFinishedCPUT());
				pScheduler->moveToBLK(runningProcess);
				runningProcess = nullptr;

			}
		}
		
		if (runningProcess && runningProcess->getFinishedCPUT() == runningProcess->getCPUT())
		{
				pScheduler->moveToTRM(runningProcess);
				runningProcess = nullptr;
		}

	}

	updateCPUstate();
	//I want to delete this method updateCPUTs();
}

bool SJF::pullFromRDY(Process*& p)
{
	if (!RDY.isEmpty())
	{
		RDY.pop(p);
		expectedFinishT -= (p->getCPUT() - p->getFinishedCPUT());
		return true;
	}
	return false;
}

void SJF::pushToRDY(Process* p)
{
	expectedFinishT += (p->getCPUT() - p->getFinishedCPUT());
	p->setProcessState(READY);
	p->setHandlingCPU(SJF_T);
	RDY.push(p);
}

void SJF::printRDYList()
{
	std::cout << RDY.size() << " RDY: ";
	RDY.print();
}
