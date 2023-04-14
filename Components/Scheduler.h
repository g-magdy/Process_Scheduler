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
public:
	Scheduler();
	/*startUp();
	readInputFile(){}
	createOutputFile()
	update();
	run();
	createProcess();
	createCPU();
	moveToRDY();
	moveToBLK();
	moveToTRM();
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