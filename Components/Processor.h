#pragma once
#include"Process.h"
#include"../DEFS.h"
class Scheduler;

class Processor
{
private:
	std::string ID;
	const CPU_TYPE CPUtype;									//enum for cpu type
	CPU_STATE CPUstate;
	int overHeatingTimeSteps;

protected:
	Process* runningProcess; // each processor type can access its running process
	int	expectedFinishT, totalBusyT, totalIdleT;
	Scheduler* const pScheduler;
	virtual void updateCPUstate();

	Process* getRunningProcess();

	void setRunningProcess(Process* runProcess);			//set runnign Process

	void setCPUstate(CPU_STATE state);						//still not sure about its implementation

	virtual void printRDYList() = 0;

	bool overHeat();

public:
	Processor(Scheduler* pscheduler, CPU_TYPE type, std::string s);		//non default constructor define total cputime =0

	virtual void scheduleAlgo(int currentTimeStep) = 0;

	virtual bool pullFromRDY(Process*& p) = 0;
	virtual void pushToRDY(Process* p) = 0;
	
	CPU_TYPE getMyType();									//you should identify the type of processor while you are creating the processor
	std::string getID();

	CPU_STATE getCPUstate();

	int getExpectedFinishT();

	//virtual bool fork() = 0;								//Used only with FCFS CPUs to deal with forkings

	void print(char printMode);								//Prints the info of the CPU in either long, short format or running Process
	float calcPLoad(int totalTurnTime );
	float calcPUtil();
	~Processor() {}
};

