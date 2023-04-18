#include "Scheduler.h"
#include <fstream>
#include<string>
using namespace std;
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
	int num_FCFS, num_SJF, num_RR;
	int timeSliceofRR;
	int minTimeToFinish, MaxWait, stealLimit, forkProb;
	int numProcesses;
	ifstream myInputFile("SampleInputFile1.txt");
	if (myInputFile.is_open())
	{
		// read into buffers
		myInputFile >> num_FCFS >> num_SJF >> num_RR;
		myInputFile >> timeSliceofRR;
		myInputFile >> minTimeToFinish >> MaxWait >> stealLimit >> forkProb;
		myInputFile >> numProcesses;
		// setdata memebers of scheduler
		numberOfCPUs = num_FCFS + num_SJF + num_RR;
		numberOfProcesses = numProcesses;
		STL = stealLimit;
		
		// create array of CPUS
		processorsGroup = new Processor * [numberOfCPUs];
		int CPU_i = 0;
		for (int i = 0; i < num_FCFS; i++)
			processorsGroup[CPU_i++] = new FCFSprocessor(this, MaxWait, forkProb);
		for (int i = 0; i < num_SJF; i++)
			processorsGroup[CPU_i++] = new SJF(this);
		for (int i = 0; i < num_RR; i++)
			processorsGroup[CPU_i++] = new RRprocessor(this, timeSliceofRR, minTimeToFinish);

		// create processes one by one
		for (int i = 0; i < numberOfProcesses; i++)
		{
			// these buffers are for one process at a time
			int arrival_t, cpu_t, numIO;
			string ID;
			myInputFile >> arrival_t >> ID >> cpu_t >> numIO;
			for (int i = 0; i < numIO; i++)
			{
				/// TODO : read pairs (t,d),(t,d),..
			}
		}
	}
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
