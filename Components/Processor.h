#pragma once
#include"Process.h"
#include"../DEFS.h"
class Scheduler;

class Processor
{
private:
	Process* runningProcess;
	int totalCPUtime;
	const CPU_TYPE CPUtype; //enum for cpu type
	CPU_STATE CPUstate;

protected:
	const Scheduler* pScheduler;
	virtual void updateCPUstate();
	void updateTotalCpuTime(int time=1);

	Process* getRunningProcess();
	void setRunningProcess(Process* runProcess);			//set runnign Process

	void setCPUstate(CPU_STATE state);						//still not sure about its implementation

public:
	Processor(Scheduler* pscheduler, CPU_TYPE type);		//non default constructor define total cputime =0

	virtual void scheduleAlgo(int currentTimeStep)=0;		//do the operation of the CPU

	virtual void pullFromRDY(Process*& p) = 0;
	virtual void pushToRDY(Process* p) = 0;
	
	CPU_TYPE getMyType();									//you should identify the type of processor while you are creating the processor

	CPU_STATE getCPUstate();

	int getTotalCpuTime();
};

