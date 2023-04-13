#include "Processor.h"

Processor::Processor(Scheduler* pscheduler)
{
	totalCPUtime = 0;
	runningProcess = nullptr;
	pScheduler = pscheduler;
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

int Processor::getTotalCpuTime()
{
	return totalCPUtime;
}
//
//void Processor::pushToBLK(Process* p)
//{
//	(*BLKptr).push(p);
//}

void Processor::setCPUtype(CPU_TYPE type)
{
	CPUtype = type;
}
