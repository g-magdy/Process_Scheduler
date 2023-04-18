#include "Scheduler.h"
#include<string>
Scheduler::Scheduler() : processorsGroup(nullptr), currentTimeStep(0), pUI(nullptr), indexOfNextCPU(0)
{
}

void Scheduler::startUp()
{
	//readInputFile();
	runningMode = pUI->startUP();
}

void Scheduler::run()
{
	while (numberOfProcesses > terminatedList.size())
	{
		currentTimeStep++;
		update();									//perform the logic of simulation
		pUI->showStatus(processorsGroup, numberOfCPUs, blockedList, terminatedList); /// may change
	}
}

void Scheduler::moveToRDY(Process* ptr)
{
	Processor* toPutRDY = processorsGroup[indexOfNextCPU % numberOfCPUs];
	toPutRDY->pushToRDY(ptr);
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


Process* Scheduler::createChild(int)
{
	return nullptr;
}

bool Scheduler::migrate(Process*, CPU_TYPE)
{
	return false;
}

bool Scheduler::kill(std::string idToKill)
{
	for (int i = 0; i < numberOfCPUs; i++)
	{
		if (processorsGroup[i]->getMyType() == FCFS_T)
		{
			if (processorsGroup[i]->kill(idToKill))
				return true;
		}
	}
	return false;
}

Scheduler::~Scheduler()
{
}

void Scheduler::readInputFile()
{
}

void Scheduler::createOutputFile()
{
}

void Scheduler::update()
{
		Process* ptr;											//to determine the processor to put the new process in 
		while (newList.Front()->getArrivalT()==currentTimeStep)
		{
			newList.pop(ptr);
			moveToRDY(ptr); 
		}

		for (int i = 0; i < numberOfCPUs; i++) {				//to fill running list of all processors
			processorsGroup[i]->scheduleAlgo(currentTimeStep);
		}

		for (int i = 0; i < numberOfCPUs; i++) {
			double randNum = random();
			if (randNum >= 1 && randNum <= 15)
			{
				processorsGroup[i]->movetoBLK();
			}
			if (randNum >= 20 && randNum <= 30)
			{
				processorsGroup[i]->movetoMyRDY();
			}
			if (randNum >= 50 && randNum <= 60)
			{
				processorsGroup[i]->movetoTRM();
			}
		}
		ptr = nullptr;
		double randNum = random();
		if (randNum <= 10)
		{
			blockedList.pop(ptr);
			moveToRDY(ptr);
		}
		
		int rand_num = random(numberOfProcesses);
		if (rand_num <= numberOfProcesses) {
			std::string id = std::to_string(rand_num);
			kill(id);
		}
		
}

Process* Scheduler::createProcess(std::string, int, int)
{
	return nullptr;
}

Processor* Scheduler::createCPU(CPU_TYPE)
{
	return nullptr;
}

bool Scheduler::steal()
{
	return false;
}

bool Scheduler::kill()
{
	return false;
}
