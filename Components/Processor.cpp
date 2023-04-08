#include "Processor.h"

Processor::Processor(CPU_TYPE type)
{
	totalCPUtime = 0;
	CPUtype = type;
}

void Processor::setRunnignProcess(Process &runProcess)
{
	runningProcess = runProcess;
}

CPU_TYPE Processor::getMyType()
{
	return CPUtype;
}
