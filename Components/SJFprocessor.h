#pragma once
#include"Processor.h"
#include"../Basic/PriorityQueue.h"

class SJF:public Processor
{
private:
	PriorityQueue <Process*> RDY;
public:
	SJF(Scheduler* pscheduler, std::string s);
	virtual void scheduleAlgo(int currentTimeStep);			
	virtual bool pullFromRDY(Process*& p);
	virtual void pushToRDY(Process* p);
	virtual void printRDYList();
	//virtual bool fork() { return false; }
};


