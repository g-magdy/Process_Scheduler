#pragma once
#include"Process.h"
#include"../DEFS.h"
class Scheduler;

class Processor
{
private:
	Process* runningProcess;
	int	expectedFinishT, totalBusyT, totalIdleT;
	std::string ID;
	const CPU_TYPE CPUtype;									//enum for cpu type
	CPU_STATE CPUstate;

protected:
	const Scheduler* pScheduler;
	virtual void updateCPUstate();
	void updateCPUTs();

	Process* getRunningProcess();
	void setRunningProcess(Process* runProcess);			//set runnign Process

	void setCPUstate(CPU_STATE state);						//still not sure about its implementation

public:
	Processor(Scheduler* pscheduler, CPU_TYPE type);		//non default constructor define total cputime =0

	virtual void scheduleAlgo(int currentTimeStep)=0;		//do the operation of the CPU

	virtual void pullFromRDY(Process*& p) = 0;
	virtual void pushToRDY(Process* p) = 0;
	
	CPU_TYPE getMyType();									//you should identify the type of processor while you are creating the processor
	std::string getID();

	CPU_STATE getCPUstate();

	int getExpectedFinishT();

	virtual bool kill(std::string idtoKill) = 0;			//Used only with FCFS CPUs to deal with killing signals
	virtual bool fork() = 0;								//Used only with FCFS CPUs to deal with forkings

	void print(char printMode);								//Prints the info of the CPU in either long, short format or running Process

	~Processor() {}
};

