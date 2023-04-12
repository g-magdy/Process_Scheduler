#include "Processor.h"

Processor::Processor()
{
	totalCPUtime = 0;
	runningProcess = nullptr;
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

CUP_STATE Processor::getCPYstate()
{
	return CPUstate;
}

void Processor::setCPUstate(CUP_STATE state)
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
