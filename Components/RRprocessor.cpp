#include "RRprocessor.h"

RRprocessor::RRprocessor(Scheduler* pscheduler) :Processor(pscheduler)
{
	setCPUtype(RR_T);
}

void RRprocessor::scheduleAlgo(int currentTimeStep)
{
	Process* ptr = getRunnignProcess();

	if (getCPUstate() == IDLE)						//related to phase one 
	{
		
		if (!RDY.empty())
		{
			pullFromRDY(ptr);							//get new process from ready list

			setRunnignProcess(ptr);						//set this process as runing process

			ptr->setProcessState(RUN);					//change the state of the new added process

			ptr->setResponseT(currentTimeStep);
		}

	}
	if (ptr)
	{
		updateTotalCpuTime();							// increament total CPU time of this processor by the cpu time of this process
		ptr->updateFinishedCPUT();						//increament the CPU time of this process}
	}
	else
		return;											//if there is no running process
	double randNum = rand() * 100;

	if (randNum >= 1 && randNum <= 15)
		//pScheduler->moveToBLK;					//move to BLK
	if (randNum >= 20 && randNum <= 30)
		//pScheduler->moveToRDY;					//move to my ready list
	if (randNum >= 50 && randNum <= 60)
		//pScheduler->moveToTRM;					//move to termination queue
	if (randNum >= 10)
		//pScheduler->movefromBLKtoRDY;				//move from IO queue to ready

	updateCPUstate();								//update CPU state 
	//need to modifiy

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



