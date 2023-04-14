#include "Processor.h"
#include"../Components/Scheduler.h"


Processor::Processor(Scheduler* pscheduler, CPU_TYPE type)
	: CPUtype(type), pScheduler(pscheduler)
{
	totalCPUtime = 0;
	runningProcess = nullptr;
	CPUstate = IDLE;
}

Process* Processor::getRunnignProcess()
{
	return runningProcess;
}

void Processor::setRunnignProcess(Process* runProcess)
{
	runningProcess = runProcess;
}

CPU_TYPE Processor::getMyType()
{
	return CPUtype;
}

CPU_STATE Processor::getCPUstate()
{
	return CPUstate;
}

void Processor::setCPUstate(CPU_STATE state)
{
	CPUstate = state;
}

void Processor::updateTotalCpuTime(int time)
{
	totalCPUtime += time;
}

void Processor::updateCPUstate()
{
	if (getRunnignProcess())	//if there is a running process 
		setCPUstate(Busy);
	else
	{
		setCPUstate(IDLE);		//where is it going to be idle
	}
}

int Processor::getTotalCpuTime()
{
	return totalCPUtime;
}
//
//void Processor::pushToBLK(Process* p)
//{
//	(*BLKptr).push(p);
//}
