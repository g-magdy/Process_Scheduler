#include "RRprocessor.h"

RRprocessor::RRprocessor(Scheduler* pscheduler, int rtf) :Processor(pscheduler, RR_T), RTF(rtf)
{
}

void RRprocessor::scheduleAlgo(int currentTimeStep)
{
	Process* ptr = nullptr;

	if (getCPUstate() == IDLE && !RDY.isEmpty())		//related to phase one 
														//if there is no a running process update it 
	{
		pullFromRDY(ptr);								//get new process from ready list

		setRunningProcess(ptr);							//set this process as runing process

		ptr->setProcessState(RUN);						//change the state of the new added process

		ptr->setResponseT(currentTimeStep);
	}

	ptr = getRunningProcess();

	if (ptr)
	{
		updateCPUTs();							// increament total CPU time of this processor by the cpu time of this process
		ptr->updateFinishedCPUT();						//increament the CPU time of this process

		//we need to handle if the Process needs IO     ******************************************************************************
	}

	updateCPUstate();											//if there is no running process
	
	double randNum = rand() * 100;

	if (randNum >= 1 && randNum <= 15)
		//pScheduler->moveToBLK;					//move to BLK
	if (randNum >= 20 && randNum <= 30)
		//pScheduler->moveToRDY;					//move to my ready list
	if (randNum >= 50 && randNum <= 60)
		//pScheduler->moveToTRM;					//move to termination queue
	if (randNum >= 10)
		//pScheduler->movefromBLKtoRDY;				//move from IO queue to ready
	;
}


void RRprocessor::pullFromRDY(Process*& p)
{
	RDY.pop(p);
}

void RRprocessor::pushToRDY(Process* p)
{
	p->setProcessState(READY);
	p->setHandlingCPU(RR_T);
	RDY.push(p);
}



