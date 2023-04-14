#pragma once
#include"Process.h"
#include"../DEFS.h"
class Scheduler;

class Processor
{
private:
	Process* runningProcess;
	int totalCPUtime;
	CPU_TYPE CPUtype; //enum for cpu type
	CPU_STATE CPUstate;

protected:
	Scheduler* pScheduler;
public:
	Processor(Scheduler* pscheduler);					//non default constructor define total cputime =0
	virtual void scheduleAlgo(int currentTimeStep)=0;				//do the operation of the CPU
	virtual void pullFromRDY(Process*& p) = 0;
	virtual void pushToRDY(Process* p) = 0;
	Process* getRunnignProcess();
	void setRunnignProcess(Process* runProcess); //set runnign Process
	CPU_TYPE getMyType();						//you should identify the type of processor while 
												//you are creating the processor
	CPU_STATE getCPUstate();
	void setCPUstate(CPU_STATE state);	//still not sure about its implementation
	void updateTotalCpuTime(int time=1);
	virtual void updateCPUstate();
	int getTotalCpuTime();
	void setCPUtype(CPU_TYPE type);
};

