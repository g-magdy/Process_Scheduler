#pragma once
#include"Processor.h"
#include"../Basic/Queue.h"

class RRprocessor:public Processor
{
private:
	Queue<Process*> RDY;
public:
	RRprocessor(Scheduler* pscheduler);
	virtual void scheduleAlgo(int currentTimeStep);				//do the operation of the CPU
	virtual void pullFromRDY(Process*& p);
	virtual void pushToRDY(Process* p);
};

