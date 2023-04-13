#include "FCFSprocessor.h"

FCFSprocessor::FCFSprocessor(Scheduler* pscheduler):Processor(pscheduler)
{
	setCPUtype(FCFS_T);
}

void FCFSprocessor::scheduleAlgo(int currentTimeStep)
{
	Process*ptr=getRunnignProcess();

	if (getCPUstate() == IDLE)						//related to phase one 												//if there is no a running process update it 
	{
		if (!RDY.isEmpty())
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
		return;							
	double randNum = rand() % 100;
	
	if(randNum>=1&&randNum<=15)
		//pScheduler->moveToBLK;					//move to BLK
	if (randNum >= 20 && randNum <= 30)
		//pScheduler->moveToRDY;					//move to my ready list
	if (randNum >= 50 && randNum <= 60)
		//pScheduler->moveToTRM;					//move to termination queue
	if(randNum>=10)
		//pScheduler->movefromBLKtoRDY;					//move from IO queue to ready
	
	
	int length=floor(rand()*RDY.getCount());		//randomly take anu process and terminate it
	//RDY.getElement(lenght)							//this fuction should return this process and delete it from the list and take the pointer by &
	updateCPUstate();								//update CPU state 												//need to modifiy

}


void FCFSprocessor::pullFromRDY(Process* & p)

{
	//RDY.pop(p);								


}

void FCFSprocessor::pushToRDY(Process* p)
{
	p->setProcessState(READY);
	p->setHandlingCPU(FCFS_T);
	//RDY.push(p);
}

