#pragma once
#include"Process.h"
#include"../DEFS.h"
class Processor
{
private:
	Process runningProcess;
	int totalCPUtime;
	CPU_TYPE CPUtype; //enum for cpu type 
public:
	Processor(CPU_TYPE type);					//default constructor define total cputime =0
	virtual void scheduleAlgo()=0;				//do the operation of the CPU
	virtual void pullFromRDY() = 0;
	virtual void pushToRDY() = 0;
	virtual void pushToBLK() = 0;
	void setRunnignProcess(Process &runProcess); //set runnign Process
	CPU_TYPE getMyType();						//you should identify the type of processor while 
											   //you are creating the processor

};

