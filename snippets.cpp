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

//#include <ctime>
//int randomPercent() //returns a value from 0 to 100
//{
//    srand(time(NULL));
//    return rand() % 100;
//}

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