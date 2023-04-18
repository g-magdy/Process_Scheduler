#include "Processor.h"
#include"../Scheduler.h"


Processor::Processor(Scheduler* pscheduler, CPU_TYPE type, std::string s)
	: CPUtype(type), pScheduler(pscheduler), ID(s)
{
	expectedFinishT = totalBusyT = totalIdleT = 0;
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
		//updateTotalCpuTime();		// increament total CPU time of this processor by the cpu time of this process
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

std::string Processor::getID()
{
	return ID;
}

void Processor::movetoBLK()
{
	Process* ptr = getRunningProcess();
	pScheduler->moveToBLK(ptr);
	setRunningProcess(nullptr);
	updateCPUstate();
}

void Processor::movetoTRM()
{
	Process* ptr = getRunningProcess();
	pScheduler->moveToTRM(ptr);
	setRunningProcess(nullptr);
	updateCPUstate();
}

void Processor::movetoMyRDY()
{
	Process* ptr = getRunningProcess();
	pushToRDY(ptr);
	setRunningProcess(nullptr);
	updateCPUstate();
}

CPU_STATE Processor::getCPUstate()
{
	return CPUstate;
}

void Processor::setCPUstate(CPU_STATE state)
{
	CPUstate = state;
}

void Processor::updateCPUTs()		//each timestep decrease the expectedFinishT and increach either the totalBusyT or totalIdleT according to the state of the CPU
{
	expectedFinishT--;					

	if (getCPUstate() == Busy)
		totalBusyT++;
	else
		totalIdleT++;
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

int Processor::getExpectedFinishT()
{
	return expectedFinishT;
}

void Processor::print(char printMode)
{
	if (printMode == 'l')
	{
		std::cout << "processor " + ID + " [";

		if (getMyType() == FCFS_T) std::cout << "FCFS";
		else if (getMyType() == SJF_T) std::cout << "SJF ";
		else if (getMyType() == RR_T) std::cout << "RR  ";

		std::cout << "]: ";
		printRDYList();
		std::cout << std::endl;
	}
	else if (printMode == 's')
		std::cout << "P" + ID;
	else if (printMode == 'r')
	{
		std::cout << *runningProcess << '(';
		print('s');
		std::cout << ')';
	}
}
