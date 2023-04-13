#include "SJFprocessor.h"

SJF::SJF(Scheduler* pscheduler):Processor(pscheduler)
{
	setCPUtype(SJF_T);
}

void SJF::scheduleAlgo(int currentTimeStep)
{
	Process* ptr = getRunnignProcess();

	if (getCPUstate() == IDLE)						//related to phase one 
		//if there is no a running process update it 
	{
		pullFromRDY(ptr);							//get new process from ready list

		setRunnignProcess(ptr);						//set this process as runing process

		updateTotalCpuTime(ptr->getCPUT());			// increament total CPU time of this processor by the cpu time of this process

		ptr->setProcessState(RUN);					//change the state of the new added process


		ptr->setResponseT(currentTimeStep);

	}
	ptr->updateFinishedCPUT();						//increament the CPU time of this process
	double randNum = rand() * 100;

	if (randNum >= 1 && randNum <= 15)
		//pScheduler->moveToBLK;					//move to BLK
	if (randNum >= 20 && randNum <= 30)
		//pScheduler->moveToRDY;					//move to my ready list
	if (randNum >= 50 && randNum <= 60)
		//pScheduler->moveToTRM;					//move to termination queue
	if (randNum >= 10)
		//pScheduler->movefromBLKtoRDY;					//move from IO queue to ready


	updateCPUstate();
}

void SJF::pullFromRDY(Process*& p)

{
	p = RDY.peek();
	RDY.remove();

}

void SJF::pushToRDY(Process* p)
{
	p->setProcessState(READY);
	p->setHandlingCPU(SJF_T);
	RDY.add(p);
}

void SJF::updateCPUstate()
{
	if (getRunnignProcess())	//if there is a running process
		setCPUstate(Busy);
	else
	{
		setCPUstate(IDLE);		//where is it going to be idle
	}
	//bool f = RDY.isEmpty();
	//if (f)	//if the list is empty		//for phase one
	//{
	//	setCPUstate(IDLE);
	//}
	//return;
}
