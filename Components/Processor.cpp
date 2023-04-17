#include "Processor.h"
#include"../Components/Scheduler.h"


Processor::Processor(Scheduler* pscheduler, CPU_TYPE type)
	: CPUtype(type), pScheduler(pscheduler)
{
	totalCPUtime = 0;
	runningProcess = nullptr;
	CPUstate = IDLE;
}

void Processor::scheduleAlgo(int currentTimeStep)
{
	Process* ptr = nullptr;

	if (getCPUstate() == IDLE )				//!RDY.isEmpty() was removed
	{
		pullFromRDY(ptr);
		setRunningProcess(ptr);
		updateCPUstate();
	}
	ptr = getRunningProcess();

	if (getCPUstate() == Busy)
	{
		updateTotalCpuTime();		// increament total CPU time of this processor by the cpu time of this process
		ptr->setResponseT(currentTimeStep);
		ptr->updateFinishedCPUT();						//increament the CPU time of this process
	}
}

Process* Processor::getRunningProcess()
{
	return runningProcess;
}

void Processor::setRunningProcess(Process* runProcess)
{
	runningProcess = runProcess;
	if(runningProcess)
		runningProcess->setProcessState(RUN);
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
	if (getRunningProcess())	//if there is a running process 
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
