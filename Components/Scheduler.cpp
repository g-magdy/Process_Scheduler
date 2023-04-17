#include "Scheduler.h"

Scheduler::Scheduler() : processorsGroup(nullptr), currentTimeStep(0), pUI(nullptr), indexOfNextCPU(0)
{
}

void Scheduler::startUp()
{
	//readInputFile();									
	//pUI->startUP();										//for phase two	
}

bool Scheduler::run()
{
	currentTimeStep = 1;
	while (NumberOfProcesses> terminatedList.size())
	{
		update();									//perform the logic of simulation
		pUI->showStatus();						
		currentTimeStep++;
	}
	return false;
}

void Scheduler::update()
{
	Process* ptr;											//to determine the processor to put the new process in 
	for (int i=0;i<NumberOfProcesses;i++)
	{
		ptr = nullptr;
		newList.pop(ptr);
		moveToRDY(ptr);
	}

	for (int i = 0; i < NumberOfCPUs; i++) {				//to fill running list of all processors
		processorsGroup[i].scheduleAlgo(currentTimeStep);
	}

	for (int i = 0; i < NumberOfCPUs; i++) {
		double randNum = random();
		ptr = processorsGroup[i].getRunningProcess();
		if (ptr)
		{
			if (randNum >= 1 && randNum <= 15)
			{
				moveToBLK(ptr);
				processorsGroup[i].setRunningProcess(nullptr);
				processorsGroup[i].updateCPUstate();
			}
			if (randNum >= 20 && randNum <= 30)
			{
				moveToRDY(ptr);
				processorsGroup[i].setRunningProcess(nullptr);
				processorsGroup[i].updateCPUstate();
			}
			if (randNum >= 50 && randNum <= 60)
			{
				moveToTRM(ptr);
				processorsGroup[i].setRunningProcess(nullptr);
				processorsGroup[i].updateCPUstate();
			}

		}

	}
	ptr = nullptr;
	double randNum = random();
	if (randNum >= 10)
	{
		blockedList.pop(ptr);
		moveToRDY(ptr);
	}			
	//int length = random(RDY.getCount());				//randomly take anu process and terminate it
	//RDY.getElement(lenght)

}

void Scheduler::moveToRDY(Process* ptr)
{
	Processor *toPutRDY=&processorsGroup[indexOfNextCPU % NumberOfCPUs];
	ptr->setHandlingCPU(toPutRDY->getMyType());
	ptr->setProcessState(READY);
	indexOfNextCPU++;
}

void Scheduler::moveToBLK(Process* ptr)
{
	ptr->setProcessState(BLOCKED);
	blockedList.push(ptr);
	//pop io request
}

void Scheduler::moveToTRM(Process* ptr)
{
	ptr->setProcessState(TERM);
	ptr->setTerminationT(currentTimeStep);
	terminatedList.push(ptr);
}


int Scheduler::random(int upperbound) const
{
	std::srand(time(NULL));
	return std::rand() % upperbound;
}

int Scheduler::getTimeStep() const
{
    return currentTimeStep;
}

void Scheduler::printCPUs() const
{
}

void Scheduler::printBLK() const
{
}

void Scheduler::printRUN() const
{
}

void Scheduler::printTRM() const
{
}

Scheduler::~Scheduler()
{
}
