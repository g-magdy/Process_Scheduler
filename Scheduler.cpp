#include "Scheduler.h"
#include <fstream>
#include<string>
#include <Windows.h>
#include <iomanip>
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
	
bool Scheduler::startUp()
{
	if (readInputFile())
	{
		runningMode = pUI->startUP();
		return true;
	}
	else
	{
		return false;
	}
}

void Scheduler::run()
{
	while (numberOfProcesses > terminatedList.size())
	{
		currentTimeStep++;
		update();									//perform the logic of simulation
	}
	createOutputFile();
}

bool Scheduler::moveToShortestRDY(Process* p, CPU_TYPE kind, bool moveToWaitingList)
{
	Processor* pShortest = nullptr;
	if (p->getMyParent())
		kind = FCFS_T;
	
	for (int i = 0; i < numberOfCPUs; i++) // I chose to loop once and check on the current CPU type
	{
		if (processorsGroup[i]->getCPUstate() != STOP && (processorsGroup[i]->getMyType() == kind || kind == NoCPU))
		{
			if (pShortest == nullptr) // if i haven't seen an FCFS yet
				pShortest = processorsGroup[i];
			else // compare with what I have currently
				pShortest = (processorsGroup[i]->getExpectedFinishT() < pShortest->getExpectedFinishT()) ? processorsGroup[i] : pShortest;
		}
	}

	if (pShortest)
	{
		pShortest->pushToRDY(p);
		return true;
	}
	else
	{
		if(moveToWaitingList)
			overHeatWaitingList.push(p);
		return false;
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
	if (ptr->getMyChild() && ptr->getMyChild()->getProcessState() != TERM)
	{
		//initiate a killing process with the id of the child
		kill(ptr->getMyChild()->getID());
	}
	if (ptr->getMySecondChild() && ptr->getMySecondChild()->getProcessState() != TERM)
	{
		kill(ptr->getMySecondChild()->getID());
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

int Scheduler::getOverHeatingPropability()
{
	return overHeatingPropability;
}


int Scheduler::getOverHeatingTimeSteps()
{
	return overHeatingTimeSteps;
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

bool Scheduler::readInputFile()
{
	int timeSliceofRR;
	int minTimeToFinish, MaxWait, stealLimit, forkProb;
	int numProcesses;
	inputfilename = pUI->getInputfilename();
	string path = "./files/input/" + inputfilename + ".txt";
	ifstream myInputFile(path);
	if (myInputFile.is_open())
	{
		// read into buffers
		myInputFile >> num_FCFS >> num_SJF >> num_RR;
		myInputFile >> timeSliceofRR;
		myInputFile >> minTimeToFinish >> MaxWait >> stealLimit >> forkProb >> overHeatingPropability >> overHeatingTimeSteps;
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
				int t, d;
				myInputFile.ignore(6, '(');
				myInputFile >> t;
				myInputFile.ignore(1, ','); 
				myInputFile >> d;
				myInputFile.ignore();
				Pair<int, int> IO_p;
				IO_p.first = t;
				IO_p.second = d;
				nPtr->pushIORquest(IO_p);
			}
			newList.push(nPtr);
		}
		// killing signal 
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
		return true;
	}
	else
	{
		pUI->print("Sorry, could not open this input file!\nPlease check the file name\n");
		return false;
	}
}

void Scheduler::createOutputFile()
{
	string path = "./files/output/" + inputfilename + "-result.txt";
	ofstream outF(path, ios::out);
	outF << setw(10) << left << "TT" << setw(10) << "PID" << setw(10) << "AT"<<setw(10)<<"CT"
		<< setw(10) << "IO_D" << setw(10) << "WT" << setw(10) << "RT"
		<< setw(10) << "TRT" << endl;

	for (int i = 0; i < numberOfProcesses; i++)
	{
		Process * ptr=terminatedList.Front();
		outF << setw(10) << left << ptr->getTerminationT() << setw(10) << ptr->getID()
			<< setw(10) << ptr->getArrivalT() << setw(10) << ptr->getCPUT() 
			<< setw(10) << ptr->getTotalIOD() << setw(10) << ptr->getWaitingT()
			<< setw(10) << ptr->getResponseT() << setw(10) << ptr->getTurnRoundT()
			<< endl;
		terminatedList.pop();
		delete ptr;
	}
	outF << "Processes:" << numberOfProcesses << endl;
	AVGWaitingT = AVGWaitingT / numberOfProcesses;
	AVGResponseT = AVGResponseT / numberOfProcesses;
	float totalTurnRoundT = AVGTurnRoundT;
	AVGTurnRoundT = AVGTurnRoundT / numberOfProcesses;
	outF << "Avg WT = " << AVGWaitingT << ','
		<< setw(10) << "Avg RT = "<< AVGResponseT 
		<<','<<setw(10)<<"Avg TRT = "<< AVGTurnRoundT<<endl;
	outF << "Migration %: " << '\t' << "RTF= "
		<< 100.00 * SucssefulMigration.first/ numberOfProcesses
		<< "%," << '\t' << "MaxW = "
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
		outF << "p" << i << "=" << processorsGroup[i]->calcPLoad(totalTurnRoundT) << '%,'<< '\t';
	}
	outF << endl<<endl;
	outF << "Processors Utiliz" << endl;
	AVGUtilisation = 0;
	for (int i = 0; i < numberOfCPUs; i++)
	{
		outF << "p" << i << "=" << processorsGroup[i]->calcPUtil() << '%,' << '\t';
		AVGUtilisation += processorsGroup[i]->calcPUtil();
	}
	outF << endl;
	AVGUtilisation = AVGUtilisation / numberOfCPUs;
	outF << "Avg utilization = " << AVGUtilisation<<'%';
	outF << endl << "Thank you Lord!";
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

	while (overHeatWaitingList.isEmpty() == false)
	{
		ptr = overHeatWaitingList.Front();
		if (moveToShortestRDY(ptr,NoCPU,false))
		{
			overHeatWaitingList.pop();
			ptr = nullptr;
		}
		else
			break;
	}

	// call scheduleAlgo function for all CPUs
	for (int i = 0; i < numberOfCPUs; i++)
	{
		processorsGroup[i]->scheduleAlgo(currentTimeStep);
	}

	//stealing function
	steal();

	//serves IO requests of the Processes wating in the BLKList
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
	// steal flag to indicate whether there was at least one successeful stealing operation or not
	bool stealFlag = false;

	if (currentTimeStep % STL != 0)
		return stealFlag;

	Processor* shortest = getShortestProcessor();
	Processor* longest = getLongestProcessor();
	if (!shortest || !longest)
		return stealFlag;

	// Helping pointer to steal, and a temp list to store the process that can't be stolen
	Process* toMove = NULL;
	List<Process*> tempList;
	double stealLimit = (100.00 * (longest->getExpectedFinishT() - shortest->getExpectedFinishT())) / longest->getExpectedFinishT();

	while (stealLimit > 40)
	{
		if (!longest->pullFromRDY(toMove)) // the longest CPU RDY list is empty
			break;

		if (!toMove->getMyParent()) // check that this process has no parent
		{
			shortest->pushToRDY(toMove);
			numOfStolenProcess++;
			stealFlag = true;
		}
		else // this is a forked process and can't be stolen
			tempList.push_back(toMove);

		// check the steal limit again
		if (longest->getExpectedFinishT()) // making sure it doesn't equal zero to avoid division by zero
			stealLimit = (100.00 * (longest->getExpectedFinishT() - shortest->getExpectedFinishT())) / longest->getExpectedFinishT();
		else break;
	}

	// return any process in the tempList before exiting the function
	if (!tempList.isEmpty()) {
		FCFSprocessor* fcfsP = dynamic_cast<FCFSprocessor*>(longest);
		while (!tempList.isEmpty())
		{
			tempList.pop_front(toMove);
			fcfsP->pushTopOfRDY(toMove);
		}
	}
	return stealFlag;
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
		pUI->print("Simulation Ends, Output file created.\n");
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
	Processor* pShortest = nullptr;

	for (int i = 0; i < numberOfCPUs; i++) // I chose to loop once and check on the current CPU type
	{
		if (processorsGroup[i]->getCPUstate() != STOP)
		{
			if (pShortest == nullptr) // if i haven't seen an FCFS yet
				pShortest = processorsGroup[i];
			else // compare with what I have currently
				pShortest = (processorsGroup[i]->getExpectedFinishT() < pShortest->getExpectedFinishT()) ? processorsGroup[i] : pShortest;
		}
	}
	return pShortest;
}

Processor* Scheduler::getLongestProcessor()
{
	Processor* pLongest = nullptr;

	for (int i = 0; i < numberOfCPUs; i++) // I chose to loop once and check on the current CPU type
	{
		if (processorsGroup[i]->getCPUstate() != STOP)
		{
			if (pLongest == nullptr) // if i haven't seen an FCFS yet
				pLongest = processorsGroup[i];
			else // compare with what I have currently
				pLongest = (processorsGroup[i]->getExpectedFinishT() > pLongest->getExpectedFinishT()) ? processorsGroup[i] : pLongest;
		}
	}
	return pLongest;
}
