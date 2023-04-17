#pragma once
#include"Processor.h"
#include"../Basic/Queue.h"
#include"../Basic/List.h"

class FCFSprocessor:public Processor
{
private:
	List<Process*> RDY;
	const int MaxW, forkProbability;
public:
	FCFSprocessor(Scheduler* pscheduler, int maxw, int forkP);
	virtual void scheduleAlgo(int currentTimeStep);				//do the operation of the CPU
	virtual void pullFromRDY(Process* & p) ;
	virtual void pushToRDY(Process* p);
	virtual void printRDYList();
	virtual bool kill(std::string idtoKill);
	virtual bool fork();
};

