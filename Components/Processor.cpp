#include "Processor.h"
#include"../Scheduler.h"


bool Processor::overHeat()
{
	if (CPUstate != STOP)
	{
		int randomNumber = pScheduler->random();

		//if the randomNumber fill with in the propapility
		if (randomNumber <= pScheduler->getOverHeatingPropability() && randomNumber > -1)
		{
			//change cpu state into stop
			CPUstate = STOP;
			//move the runnig process
			if (runningProcess)
			{
				pScheduler->moveToShortestRDY(runningProcess);
				runningProcess = nullptr;
			}
			//move all the process in the rdy list
			Process* tempPtr = nullptr;
			while (pullFromRDY(tempPtr))
			{
				pScheduler->moveToShortestRDY(tempPtr);
				tempPtr = nullptr;
			}
			//get the heating time steps
			overHeatingTimeSteps = pScheduler->getOverHeatingTimeSteps();
			return true;
		}
		else
			return false;
	}
	else
	{
		overHeatingTimeSteps--;

		if (overHeatingTimeSteps <= 0) //if it has spend the overheating time
		{
			CPUstate = IDLE;
			return false;
		}
		else
			return true;
	}
}

Processor::Processor(Scheduler* pscheduler, CPU_TYPE type, std::string s)
	: CPUtype(type), pScheduler(pscheduler), ID(s)
{
	expectedFinishT = totalBusyT = totalIdleT = 0;
	overHeatingTimeSteps = 0;
	runningProcess = nullptr;
	CPUstate = IDLE;
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

CPU_STATE Processor::getCPUstate()
{
	if (CPUstate == STOP)
		return STOP;

	if (runningProcess)
		return Busy;
	else
		return IDLE;
}

void Processor::setCPUstate(CPU_STATE state)
{
	CPUstate = state;
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

float Processor::calcPLoad(int totalTurnAroundTime)
{
	return ((float)totalBusyT / totalTurnAroundTime) * 100;
}

float Processor::calcPUtil()
{
	return ((float)totalBusyT / (totalBusyT + totalIdleT)) * 100;
}
