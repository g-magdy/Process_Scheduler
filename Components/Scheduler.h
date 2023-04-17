#pragma once
#include "../Components/Process.h"
#include "../Components/Processor.h"
#include "../Components/FCFSprocessor.h"
#include "../Components/SJFprocessor.h"
#include "../Components/RRprocessor.h"
#include "../Components/UI.h"

class UI;

class Scheduler
{
private:
	Processor* processorsGroup;
	Queue<Process*> newList;
	Queue<Process*> blockedList;
	Queue<Process*> terminatedList;
	int currentTimeStep;
	UI* pUI;
	int NumberOfProcesses;
	int NumberOfCPUs;
	int indexOfNextCPU;
public:
	Scheduler();
	void startUp();
	bool run();
	void update();
	void moveToRDY(Process * ptr);
	void moveToBLK(Process* ptr);
	void moveToTRM(Process* ptr);
	//readInputFile();
	//createOutputFile()
	/*createProcess();
	createCPU();
	steal();
	createChild();*/
	int random(int upperbound = 100) const; //returns a value from 0 to 100
	int getTimeStep() const;
	void printCPUs() const;
	void printBLK() const;
	void printRUN() const;
	void printTRM() const;

	~Scheduler();
};