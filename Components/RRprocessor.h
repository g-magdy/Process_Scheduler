#pragma once
#include"Processor.h"
#include"../Basic/Queue.h"

class RRprocessor:public Processor
{
private:
	Queue<Process*> RDY;
	const int RTF;
public:
	RRprocessor(Scheduler* pscheduler, int rtf);
	virtual void scheduleAlgo(int currentTimeStep);				//do the operation of the CPU
	virtual void pullFromRDY(Process*& p);
	virtual void pushToRDY(Process* p);
	virtual bool kill(std::string idtoKill) {}
	virtual bool fork() {}
};

