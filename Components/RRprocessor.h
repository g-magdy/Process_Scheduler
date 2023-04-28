#pragma once
#include"Processor.h"
#include"../Basic/Queue.h"

class RRprocessor:public Processor
{
private:
	Queue<Process*> RDY;
	const int RTF;
	const int timeSlice;
public:
	RRprocessor(Scheduler* pscheduler, std::string s,int tslice, int rtf);
	virtual void scheduleAlgo(int currentTimeStep);				//do the operation of the CPU
	virtual bool pullFromRDY(Process*& p);
	virtual void pushToRDY(Process* p);
	virtual void printRDYList();
	virtual bool fork() { return false; }
};

