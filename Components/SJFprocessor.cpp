#include "SJFprocessor.h"

SJF::SJF(Scheduler* pscheduler, std::string s):Processor(pscheduler, SJF_T, s)
{
}

void SJF::scheduleAlgo(int currentTimeStep)
{
	Process* runningProcess = getRunningProcess();
	if (!runningProcess) {

		if (pullFromRDY(runningProcess)) {
			setRunningProcess(runningProcess);
			runningProcess->setResponseT(currentTimeStep - runningProcess->getArrivalT());
			expectedFinishT += runningProcess->getCPUT();

		}
		else {
			totalIdleT++;
		}

	}
	if (runningProcess)
	{
		totalBusyT++;
		runningProcess->updateFinishedCPUT();
		Pair<int, int> p;
		if (runningProcess->peekNextIOR(p)) {

			if (p.first == currentTimeStep)
			{
				expectedFinishT -= (runningProcess->getCPUT() - runningProcess->getFinishedCPUT());
				//pScheduler->moveToBLK(runningProcess);
				setRunningProcess(nullptr);
				runningProcess = nullptr;

			}
		}
		else
			if (currentTimeStep == runningProcess->getTerminationT()) {
				//pScheduler->moveToTRM(ptr);
				setRunningProcess(nullptr);
				runningProcess = nullptr;
				expectedFinishT--;
			}
			else
				expectedFinishT--;

	}

	updateCPUstate();
	//I want to delete this method updateCPUTs();
}

bool SJF::pullFromRDY(Process*& p)
{
	if (!RDY.isEmpty())
	{
		RDY.pop(p);
		return true;
	}
	return false;
}

void SJF::pushToRDY(Process* p)
{
	p->setProcessState(READY);
	p->setHandlingCPU(SJF_T);
	RDY.push(p);
}

void SJF::printRDYList()
{
	std::cout << RDY.size() << " RDY: ";
	RDY.print();
}
