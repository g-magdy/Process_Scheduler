#pragma once
#include"Processor.h"
#include"../Basic/PriorityQueue.h"

class SJF:public Processor
{
private:
	PriorityQueue <Process*> RDY;
public:
	SJF(Scheduler* pscheduler);
	virtual void scheduleAlgo(int currentTimeStep);			
	virtual void pullFromRDY(Process*& p);
	virtual void pushToRDY(Process* p);
};


