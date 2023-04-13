#pragma once
#include"Processor.h"
#include"../Basic/Queue.h"
#include"../Basic/List.h"
class Processor;
class FCFSprocessor:public Processor
{
private:
	List<Process*> RDY;
public:
	FCFSprocessor(Scheduler* pscheduler);
	virtual void scheduleAlgo(int currentTimeStep);				//do the operation of the CPU
	virtual void pullFromRDY(Process* & p) ;
	virtual void pushToRDY(Process* p);
	virtual void updateCPUstate();
};

