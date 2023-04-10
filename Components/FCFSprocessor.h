#pragma once
#include"Processor.h"
#include"../Basic/Queue.h"
class FCFSprocessor:public Processor
{
private:
	Queue<Process*> RDYlist;
	
public:
	FCFSprocessor(CPU_TYPE type = FCFS_T);
	virtual void scheduleAlgo();				//do the operation of the CPU
	virtual void pullFromRDY(Process* & p) ;
	virtual void pushToRDY(Process* p);
	virtual void updateCPUstate();
};

