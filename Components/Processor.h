#pragma once
#include"Process.h"
#include"../DEFS.h"
class Processor
{
private:
	Process* runningProcess;
	int totalCPUtime;
	Queue<Process*> * BLKptr; //common for All processor
	CPU_TYPE CPUtype; //enum for cpu type
	CUP_STATE CPUstate;
public:
	Processor(CPU_TYPE type);					//non default constructor define total cputime =0
	virtual void scheduleAlgo()=0;				//do the operation of the CPU
	virtual void pullFromRDY() = 0;
	virtual void pushToRDY(Process & p) = 0;
	Process* getRunnignProcess();
	void setRunnignProcess(Process* &runProcess); //set runnign Process
	CPU_TYPE getMyType();						//you should identify the type of processor while 
												//you are creating the processor
	CUP_STATE getCPYstate();
	void setCPUstate(CUP_STATE state);	//still not sure about its implementation
	void updateTotalCpuTime(int time=1);
	virtual void updateCPUstate()=0;
	int getTotalCpuTime();
	void pushToBLK(Process* p);
};

