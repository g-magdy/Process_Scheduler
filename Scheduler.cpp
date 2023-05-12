#include "Scheduler.h"
#include <fstream>
#include<string>
#include <Windows.h>
using namespace std;
Scheduler::Scheduler() : processorsGroup(nullptr), currentTimeStep(0), pUI(nullptr), indexOfNextCPU(0), randHelper(0),numOfForkedProcess(0), numOfKillededProcess(0), numOfStolenProcess(0)
{
	pUI = new UI(this);
}

void Scheduler::startUp()
{
}

void Scheduler::run()
{
}

void Scheduler::moveToShortestRDY(Process* p, CPU_TYPE kind)
{
	Processor* shortestFCFS, * shortestSJF, * shortestRR;
	shortestFCFS = shortestSJF = shortestRR = nullptr; // initially I can't assume
	for (int i = 0; i < numberOfCPUs; i++) // I chose to loop once and check on the current CPU type
	{
		Processor* pCPU = processorsGroup[i];
		if (pCPU->getMyType() == FCFS_T)
		{
			if (shortestFCFS == nullptr) // if i haven't seen an FCFS yet
				shortestFCFS = pCPU;
			else // compare with what I have currently
				shortestFCFS = (pCPU->getExpectedFinishT() < shortestFCFS->getExpectedFinishT()) ? pCPU : shortestFCFS;
		}
		else if (pCPU->getMyType() == SJF_T)
		{
			if (shortestSJF == nullptr) // if i haven't seen an SJF yet
				shortestSJF = pCPU;
			else
				shortestSJF = (pCPU->getExpectedFinishT() < shortestSJF->getExpectedFinishT()) ? pCPU : shortestSJF;
		}
		else // RR CPU
		{
			if (shortestRR == nullptr) // if i haven't seen an RR yet
				shortestRR = pCPU;
			else
				shortestRR = (pCPU->getExpectedFinishT() < shortestRR->getExpectedFinishT()) ? pCPU : shortestRR;
		}
	}
	if (kind == FCFS_T)
		shortestFCFS->pushToRDY(p);
	else if (kind == SJF_T)
		shortestSJF->pushToRDY(p);
	else if (kind == RR_T)
		shortestRR->pushToRDY(p);
	else // kind is any general CPU
	{
		Processor* pShortest = (shortestFCFS->getExpectedFinishT() < shortestSJF->getExpectedFinishT()) ? shortestFCFS : shortestSJF;
		pShortest = (shortestRR->getExpectedFinishT() < pShortest->getExpectedFinishT()) ? shortestRR : pShortest;
		pShortest->pushToRDY(p);
	}
}

void Scheduler::moveToBLK(Process* ptr)
{
	ptr->setProcessState(BLOCKED);
	blockedList.push(ptr);
	//pop io request
	///EDIT: i will just peek first request and pop it only when it is fully served
}

void Scheduler::moveToTRM(Process* ptr)
{
	ptr->setProcessState(TERM);
	ptr->setTerminationT(currentTimeStep);
	/// TODO: ptr->setTurnAroundTime(currentTimeStep - ptr->getArrivalT());
	terminatedList.push(ptr);
	// check if the terminated process has childred
	if (ptr->getMyChild())
	{
		//initiate a killing process with the id of the child
		kill(ptr->getMyChild()->getID());
	}
}


int Scheduler::random(int upperbound)
{
	std::srand(time(NULL) * randHelper++);
	return std::rand() % upperbound;
}

int Scheduler::getTimeStep() const
{
    return currentTimeStep;
}


Process* Scheduler::createChild(int ct)
{
	Process* child = new Process(to_string(++numberOfProcesses), currentTimeStep, ct);
	numOfForkedProcess++;
	moveToShortestRDY(child, FCFS_T);
	return child;
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
			if ( ((FCFSprocessor*)processorsGroup[i])->kill(idToKill))
			{
				numOfKillededProcess++;
				return true;
			}

		}
	}
	return false;
}

//bool Scheduler::fork(std::string id, int AT, int CPUT)
//{
//	Process* child = new Process(id,AT,CPUT);
//	mo
//	return false;
//}

void Scheduler::simulation()
{
	readInputFile();
	runningMode = pUI->startUP();

	while (numberOfProcesses > terminatedList.size())
	{
		currentTimeStep++;

		Process* ptr;											//to determine the processor to put the new process in 
		while (!newList.isEmpty() && newList.Front()->getArrivalT() == currentTimeStep)
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
			if (!blockedList.isEmpty())
			{
				blockedList.pop(ptr);
				moveToRDY(ptr);
			}
		}

		int rand_num = random(numberOfProcesses);
		if (rand_num <= numberOfProcesses) {
			std::string id = std::to_string(rand_num);
			kill(id);
		}

		updateConsole();
	}
}

Scheduler::~Scheduler()
{
	Process* toDelete;

	while (!terminatedList.isEmpty())
	{
		terminatedList.pop(toDelete);
		delete toDelete;
		toDelete = nullptr;
	}
	for (int i = 0; i < numberOfCPUs; i++)
	{
		delete processorsGroup[i];
	}
	delete[]processorsGroup;
	delete pUI;
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
			processorsGroup[CPU_i++] = new FCFSprocessor(this, to_string(CPU_i+1), MaxWait, forkProb);
		for (int i = 0; i < num_SJF; i++)
			processorsGroup[CPU_i++] = new SJF(this, to_string(CPU_i+1));
		for (int i = 0; i < num_RR; i++)
			processorsGroup[CPU_i++] = new RRprocessor(this, to_string(CPU_i+1), timeSliceofRR, minTimeToFinish);

		// create processes one by one
		for (int j = 0; j < numberOfProcesses; j++)
		{
			// these buffers are for one process at a time
			int arrival_t, cpu_t, numIO;
			string ID;
			myInputFile >> arrival_t >> ID >> cpu_t >> numIO;
			Process* nPtr = new Process(ID, arrival_t, cpu_t);
			for (int i = 0; i < numIO; i++)
			{
				/// TOTEST : read pairs (t,d),(t,d),..
				int t, d;
				myInputFile.ignore(6, '(');
				myInputFile >> t;
				myInputFile.ignore(1, ','); /// there is a problem here ?
				myInputFile >> d;
				myInputFile.ignore();
				Pair<int, int> IO_p;
				IO_p.first = t;
				IO_p.second = d;
				nPtr->pushIORquest(IO_p);
			}
			newList.push(nPtr);
		}
		///TOTEST : killing signal 
		while (!myInputFile.eof())
		{
			int at;
			string s;
			myInputFile >> at >> s;
			Pair<int, string> p;
			p.first = at;
			p.second = s;
			killList.push(p);
		}
	}
}

void Scheduler::createOutputFile()
{
}

void Scheduler::update()
{
}

//Process* Scheduler::createProcess(std::string, int, int)
//{
//	return nullptr;
//}

Processor* Scheduler::createCPU(CPU_TYPE)
{
	return nullptr;
}

bool Scheduler::steal()
{
	if (currentTimeStep % STL == 0)
	{
		Processor* shortest = getShortestProcessor();
		Processor* longest = getLongestProcessor();
		Process* toMove;
		bool stealFlag = false;
		double stealLimit = (100.00 * (longest->getExpectedFinishT() - shortest->getExpectedFinishT())) / longest->getExpectedFinishT();
		while (stealLimit > 40)
		{
			if (longest->pullFromRDY(toMove)) {
				if (!toMove->getParent()) {
					shortest->pushToRDY(toMove);
				}
				else
				{
					Process** forkedProcess = new Process*[numOfForkedProcess];
					forkedProcess[0] = toMove;
					for (int i = 1; i < numOfForkedProcess; i++)
					{
						if (longest->pullFromRDY(toMove))
						{
							if (!toMove->getParent()) {
								shortest->pushToRDY(toMove);
								FCFSprocessor* fcfsP = dynamic_cast<FCFSprocessor*>(longest);
								for (int j = i-1; j <=0; j--)
								{
									fcfsP->pushTopOfRDY(forkedProcess[j]);
								}
								numOfStolenProcess++;
								stealFlag = true;
								break;

							}
							else
							{
								forkedProcess[i] = toMove;

							}
							
						}
						else
						{
							FCFSprocessor* fcfsP = dynamic_cast<FCFSprocessor*>(longest);
							for (int j = i - 1; j <= 0; j--)
							{
								fcfsP->pushTopOfRDY(forkedProcess[j]);
							}
							return stealFlag;
						}
					}
				}



			}
			else
				return stealFlag;
			stealLimit = (100.00 * (longest->getExpectedFinishT() - shortest->getExpectedFinishT())) / longest->getExpectedFinishT();
		}

	}
	else
		return 0;

}

bool Scheduler::kill()
{
	//First check that the killList is not empty
	if (killList.isEmpty() == false)
	{
		//make a pair to take a peak on the front element of the KillList
		Pair<int, string> killSig;
		killSig = killList.Front(); 

		//check if the kill signal is in this time step
		if (killSig.first == currentTimeStep)
		{
			//remove the killing signal from the list
			killList.pop();
			//call kill(string) that iterates on the cpus to kill the process with the given id
			kill(killSig.second);
		}
	}
}

void Scheduler::updateConsole()
{
	if (runningMode == INTERACTIVE)
	{
		pUI->showStatus(processorsGroup, numberOfCPUs, blockedList, terminatedList); /// may change
		pUI->getInput();
	}
	else if (runningMode == STEPBYSTEP)
	{
		pUI->showStatus(processorsGroup, numberOfCPUs, blockedList, terminatedList); /// may change
		Sleep(1000);
	}

	if (numberOfProcesses <= terminatedList.size())
	{
		pUI->print("Simulation Ends, Output file created.");
	}
}

void Scheduler::serveIO()
{
	// first: check if there is a process in BLK
	if (!blockedList.isEmpty())
	{
		Process* customer = blockedList.Front(); // just a temp pointer
		if (customer->getProcessState() == BLOCKED)
			customer->setProcessState(IO);

		customer->incrementServedIODuration();
		// second: the processes in the blocked list will always have requests
		// checked before calling moveTOBLK()
		Pair <int, int>req;
		customer->peekNextIOR(req);
		if (customer->getServedIODuration() == req.second) // IO duration is finished
		{
			customer->popkNextIOR(req); // request was completed
			blockedList.pop(); // remove the customer from the blocked list
			customer->resetServedIODuration(); // to prepare for the next request
			moveToShortestRDY(customer);
		}
	}
}

Processor* Scheduler::getShortestProcessor()
{
	Processor* shortest = processorsGroup[0];

	for (int i = 1; i < numberOfCPUs; i++)
	{
		if (shortest->getExpectedFinishT() > processorsGroup[i]->getExpectedFinishT())
		{
			shortest = processorsGroup[i];
		}

	}
	return shortest;
}

Processor* Scheduler::getLongestProcessor()
{
	Processor* longest = processorsGroup[0];
	for (int i = 1; i < numberOfCPUs; i++)
	{
		if (longest->getExpectedFinishT() < processorsGroup[i]->getExpectedFinishT())
		{
			longest = processorsGroup[i];
		}

	}
	return longest;
}
