#include "FCFSprocessor.h"

FCFSprocessor::FCFSprocessor(CPU_TYPE type=FCFS_T):Processor(type)
{
}

void FCFSprocessor::scheduleAlgo()
{
	Process*ptr=getRunnignProcess();
	if (ptr)						// you should set running process with null after each deletion
		ptr->updateFCT();			//if there is a running process update it 
	else
	{
		pullFromRDY(ptr);
		setRunnignProcess(ptr);
		setCPUstate(Busy);
		updateTotalCpuTime();
		ptr->setProcessState(RUN);
		ptr->updateFCT();
		ptr->setHandlingCPU(FCFS_T);
		//ptr->setRT();
		
	}


}


void FCFSprocessor::pullFromRDY(Process*& p)
{
	RDYlist.pop(p);
}

void FCFSprocessor::pushToRDY(Process* & p)
{
	RDYlist.push(p);
}

void FCFSprocessor::updateCPUstate()
{
	if (getRunnignProcess())	//if there is a running process 
		setCPUstate(Busy);

	if (RDYlist.empty())	//if the list is empty
	{
		setCPUstate(IDLE);
	}
	
		
}
