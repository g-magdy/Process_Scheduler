/*
* In this file we will collect all of our random little coding ideas
* and functions and non complete implementations
* NO JUDGEMENT - BRAINSTORMING
*/

// ===============
//      ENUMS
// ===============

enum PROCESS_STATE
{
    NEW,
    READY,
    RUNNING,
    BLOCKED,
    TERMINATED,
    ORPHAN
};

enum CPU_TYPE
{
    FCFS,
    SJF,
    RR
};

enum CPU_STATE
{
    IDLE,
    BUSY
};

/* // old list test
	string items[] = { "one", "two", "three", "four", "five", "six" };

	for (int i = 0; i < 6; i++)
	{
		listPtr->push_back(items[i]);
	}


	cout << "printing then clearing list using remove front while it is not emty ::\n";
	while (!listPtr->isEmpty())
	{
		cout << listPtr->front() << " ";
		listPtr->pop_front();
	}
	cout << "\nIs empty : " << listPtr->isEmpty() << " (should be 1)\n";
	cout << "Count : " << listPtr->getCount() << " (should be 0)\n\n";

	cout << "New data ..\n";
	for (int i = 0; i < 3; i++)
	{
		listPtr->push_front(items[i]);
		listPtr->push_back(items[i]);
	}
	cout << "Is empty : " << listPtr->isEmpty() << " (should be 0)\n";
	cout << "Count : " << listPtr->getCount() << " (should be 6)\n\n";

	cout << "clearing list using remove last while it is not emty ::\n";
	while (!listPtr->isEmpty())
	{
		listPtr->pop_back();
	}
	cout << "Is empty : " << listPtr->isEmpty() << " (should be 1)\n";
	cout << "Count : " << listPtr->getCount() << " (should be 0)\n\n";
*/
//Schedule Algo
//Process* ptr = nullptr;

	//if (getCPUstate() == IDLE && !RDY.isEmpty())		//related to phase one 
	//													//if there is no a running process update it 
	//{
	//	pullFromRDY(ptr);								//get new process from ready list

	//	setRunningProcess(ptr);							//set this process as runing process

	//	ptr->setProcessState(RUN);						//change the state of the new added process

	//	ptr->setResponseT(currentTimeStep);
	//}

	//ptr = getRunningProcess();

	//if (ptr)
	//{
	//	updateTotalCpuTime();							// increament total CPU time of this processor by the cpu time of this process
	//	ptr->updateFinishedCPUT();						//increament the CPU time of this process

	//	//we need to handle if the Process needs IO     ******************************************************************************
	//}

	//updateCPUstate();											//if there is no running process
	//
	//double randNum = rand() * 100;

	//if (randNum >= 1 && randNum <= 15)
	//	//pScheduler->moveToBLK;					//move to BLK
	//if (randNum >= 20 && randNum <= 30)
	//	//pScheduler->moveToRDY;					//move to my ready list
	//if (randNum >= 50 && randNum <= 60)
	//	//pScheduler->moveToTRM;					//move to termination queue
	//if (randNum >= 10)
	//	//pScheduler->movefromBLKtoRDY;				//move from IO queue to ready
	//;

//{
	//when adding a new process to the cpu
	//exptectedFinishTime += process.cputime - process.finishedcputime;
	
	//when sending a process to BLK list
	//exptectedFinishTime -= process.cputime - process.finishedcputime;
	
	//in the schduleAlgo decrease the expectedFinishTime by 1

//}