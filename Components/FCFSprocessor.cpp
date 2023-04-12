#include "FCFSprocessor.h"

FCFSprocessor::FCFSprocessor()
{
	setCPUtype(FCFS_T);
}

void FCFSprocessor::scheduleAlgo()
{
	Process*ptr=getRunnignProcess();

	if (ptr)						// you should set running process with null after each deletion
		ptr->updateFinishedCPUT();			//if there is a running process update it 
	else
	{
		//check if the queue is not empty 
		pullFromRDY(ptr);			//get new process from ready list

		setRunnignProcess(ptr);		//set this process as runing process

		/*updateCPUstate();*/			//undate CPU state 

		updateTotalCpuTime();		// increament total CPU time of this processor by 1

		ptr->setProcessState(RUN);	//change the state of the new added process

		ptr->updateFinishedCPUT();			//increament the CPU time of this process

		//ptr->setRT();
		
	}


}


void FCFSprocessor::pullFromRDY(Process* & p)
{
	RDYlist.pop(p);
}

void FCFSprocessor::pushToRDY(Process* p)
{
	RDYlist.push( p);
}

void FCFSprocessor::updateCPUstate()
{
	if (getRunnignProcess())	//if there is a running process 
		setCPUstate(Busy);
	bool f=RDYlist.empty();
	if (f)	//if the list is empty
	{
		setCPUstate(IDLE);
	}
	return;
		
}
