#include "Scheduler.h"
#include <fstream>
#include<string>
#include <Windows.h>
using namespace std;

void Scheduler::calcStatiscs(Process* ptr)
{
	AVGWaitingT += ptr->getWaitingT();
	AVGResponseT += ptr->getResponseT();
	AVGTurnRoundT += ptr->getTurnRoundT();
}

Scheduler::Scheduler() : processorsGroup(nullptr), currentTimeStep(0), pUI(nullptr), indexOfNextCPU(0), randHelper(0),numOfForkedProcess(0), numOfKilledProcess(0), numOfStolenProcess(0)
{
	pUI = new UI(this);
	SucssefulMigration.first = SucssefulMigration.second = 0;
	STL = 0;
	stealPercentage = killPercentage = forkPercentage = 0;
	runningMode = SILENT; // this is just an initial value
	numberOfProcesses = numberOfCPUs = 0;
	AVGResponseT = AVGTurnRoundT = AVGUtilisation = AVGWaitingT = 0;
}
	
void Scheduler::startUp()
{
	readInputFile();
	runningMode = pUI->startUP();
}

void Scheduler::run()
{
	while (numberOfProcesses > terminatedList.size())
	{
		currentTimeStep++;
		update();									//perform the logic of simulation
	}
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
		Processor* pShortest = (shortestFCFS->getExpectedFinishT() <= shortestSJF->getExpectedFinishT()) ? shortestFCFS : shortestSJF;
		pShortest = (shortestRR->getExpectedFinishT() <= pShortest->getExpectedFinishT()) ? shortestRR : pShortest;
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
	calcStatiscs(ptr);
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


Process* Scheduler::createChild(int ct, Process* parent)
{
	Process* child = new Process(to_string(++numberOfProcesses), currentTimeStep, ct);
	child->setMyParent(parent);

	numOfForkedProcess++;
	moveToShortestRDY(child, FCFS_T);
	return child;
}

bool Scheduler::migrate(Process* ptr, CPU_TYPE Destination_kind)
{
	if (Destination_kind == RR_T)
	{
		moveToShortestRDY(ptr, RR_T);
		SucssefulMigration.second++;
		return true;
	}
	else if (Destination_kind == SJF_T)
	{
		moveToShortestRDY(ptr, SJF_T);
		SucssefulMigration.first++;
		return true;
	}
	else
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
				numOfKilledProcess++;
				return true;
			}

		}
	}
	return false;
}


void Scheduler::simulation()
{
	Process* ptr;

	while (numberOfProcesses > terminatedList.size())
	{
		currentTimeStep++;

		for (int i = 0; i < numberOfCPUs; i++) {				//to fill running list of all processors
			processorsGroup[i]->scheduleAlgo(currentTimeStep);
		}

		/*for (int i = 0; i < numberOfCPUs; i++) {
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
		}*/

		ptr = nullptr;
		double randNum = random();
		if (randNum <= 10)
		{
			if (!blockedList.isEmpty())
			{
				blockedList.pop(ptr);
				//moveToRDY(ptr);
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
	for (int i = 0; i < numberOfCPUs; i++)
	{
		delete processorsGroup[i];
	}
	delete[]processorsGroup;
	delete pUI;
}

void Scheduler::readInputFile()
{
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
	ofstream outF("sampleOutput.txt", ios::out);
	outF << "TT" << "    " << "PID" << "    " << "AT"<<"    "<<"CT"
		<< "    " << "IO_D" << "    " << "WT" << "    " << "RT"
		<< "    " << "TRT" << endl;
	for (int i = 0; i < numberOfProcesses; i++)
	{
		Process * ptr=terminatedList.Front();
		terminatedList.pop();
		outF << ptr->getTerminationT() << "    " << ptr->getID() 
			<< "    " << ptr->getArrivalT() << "    " << ptr->getCPUT() 
			<< "    " << ptr->getTotalIOD() << "    " << ptr->getWaitingT()
			<< "    " << ptr->getResponseT() << "    " << ptr->getTurnRoundT()
			<< endl;
		delete ptr;
	}
	outF << "Processes:" << numberOfProcesses << endl;
	AVGWaitingT = AVGWaitingT / numberOfProcesses;
	AVGResponseT = AVGResponseT / numberOfProcesses;
	float totalTurnRoundT = AVGTurnRoundT;
	AVGTurnRoundT = AVGTurnRoundT / numberOfProcesses;
	outF << "Avg WT = " << AVGWaitingT << ','
		<< "    " << "Avg RT = "<< AVGResponseT 
		<<','<<"    "<<"Avg TRT = "<< AVGTurnRoundT<<endl;
	outF << "Migration %: " << "    " << "RTF= " 
		<< 100.00 * SucssefulMigration.first/ numberOfProcesses
		<< "%," << "    "<< "MaxW = "
		<< 100.00 * SucssefulMigration.second / numberOfProcesses
		<< "%" << endl;	
	stealPercentage = 100.00 * numOfStolenProcess / numberOfProcesses;
	forkPercentage=100.00*numOfForkedProcess/ numberOfProcesses;
	killPercentage=100.00*numOfKilledProcess/ numberOfProcesses;

	outF << "Work Steal%: " << stealPercentage <<"%" <<endl;
	outF << "Forked Process: " << forkPercentage << "%" << endl;
	outF << "Killed Process: " << killPercentage << "%" << endl<<endl;

	outF << "Processors:" << numberOfCPUs << " [" << num_FCFS<<"FCFS, " 
		<< num_SJF << "SJF, "<<num_RR << "RR "<< "]" << endl;
	outF << "Processors Load " << endl;
	for (int i = 0; i < numberOfCPUs; i++)
	{
		outF << "p" << i << "=" << processorsGroup[i]->calcPLoad(totalTurnRoundT) << '%,'<< "    ";
	}
	outF << endl<<endl;
	outF << "Processors Utiliz" << endl;
	AVGUtilisation = 0;
	for (int i = 0; i < numberOfCPUs; i++)
	{
		outF << "p" << i << "=" << processorsGroup[i]->calcPUtil() << '%,' << "    ";
		AVGUtilisation += processorsGroup[i]->calcPUtil();
	}
	outF << endl;
	AVGUtilisation = AVGUtilisation / numberOfCPUs;
	outF << "Avg utilization = " << AVGUtilisation<<'%';
	outF.close();
}

void Scheduler::update()
{
	Process* ptr;

	// Distripute new arriving Processes at this time step
	while (!newList.isEmpty() && newList.Front()->getArrivalT() == currentTimeStep)
	{
		newList.pop(ptr);
		moveToShortestRDY(ptr);
	}

	// call scheduleAlgo function for all CPUs
	for (int i = 0; i < numberOfCPUs; i++)
	{
		processorsGroup[i]->scheduleAlgo(currentTimeStep);
	}

	/// TODO: activate the stealing function
	steal();

	//serves IO requests of the Processes wating in the BLKList
	/// TODO: activeate serveIO funcion
	serveIO();

	//Check for Killing signals at this time step
	kill();

	//update the console
	updateConsole();
}

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
				if (!toMove->getMyParent()) {
					shortest->pushToRDY(toMove);
					numOfStolenProcess++;
					stealFlag = true;
				}
				else
				{
					Process** forkedProcess = new Process*[numOfForkedProcess];
					forkedProcess[0] = toMove;
					for (int i = 1; i < numOfForkedProcess; i++)
					{
						if (longest->pullFromRDY(toMove))
						{
							if (!toMove->getMyParent()) {
								shortest->pushToRDY(toMove);
								FCFSprocessor* fcfsP = dynamic_cast<FCFSprocessor*>(longest);
								for (int j = i-1; j <=0; j--)
								{
									fcfsP->pushTopOfRDY(forkedProcess[j]);
								}
								delete []forkedProcess;
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
							delete[]forkedProcess;
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
	//A flag to indicate whether a killing process has done successufully or not
	bool successKill = false;

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
			successKill = kill(killSig.second);
		}
	}

	return successKill;
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
			customer->incrementTotalIOD(req.second);
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
