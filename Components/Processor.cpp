#include "Processor.h"

Processor::Processor(CPU_TYPE type)
{
	totalCPUtime = 0;
	CPUtype = type;
	runningProcess = nullptr;
}

Process* Processor::getRunnignProcess()
{
	return runningProcess;
}

void Processor::setRunnignProcess(Process* &runProcess)
{
	runningProcess = runProcess;
}

CPU_TYPE Processor::getMyType()
{
	return CPUtype;
}

CPU_STATE Processor::getCPYstate()
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

void Processor::pushToBLK(Process* p)
{
	(*BLKptr).push(p);
}
