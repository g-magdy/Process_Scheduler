#pragma once
#include "Components/Process.h"
#include "Components/Processor.h"
#include "Components/FCFSprocessor.h"
#include "Components/SJFprocessor.h"
#include "Components/RRprocessor.h"
#include "Components/UI.h"

class UI;

class Scheduler
{
private:
	Processor** processorsGroup;
	int numberOfCPUs;
	Queue<Process*> newList;
	Queue<Process*> blockedList;
	Queue<Process*> terminatedList;
	Queue<Process*> overHeatWaitingList;
	Queue<Pair<int, std::string>> killList;
	int currentTimeStep;
	int numberOfProcesses;
	UI* pUI;
	std::string latestID;
	int STL;
	RunningMode runningMode;
	int indexOfNextCPU;
	int randHelper;
	std::string inputfilename;
  
	int num_FCFS, num_SJF, num_RR;
	int overHeatingPropability, overHeatingTimeSteps;
  
	int numOfForkedProcess;
	int numOfKilledProcess;
	int numOfStolenProcess;
	//statistics attributes
	float AVGWaitingT, AVGResponseT, AVGTurnRoundT;
	Pair<float,float> SucssefulMigration;
	float stealPercentage;
	float  killPercentage;
	float  forkPercentage;
	float  AVGUtilisation;
	//private functions
	bool readInputFile();
	void createOutputFile();
	void update();
	//Process* createProcess(std::string, int, int);
	Processor* createCPU(CPU_TYPE);
	bool steal();
	bool kill();
	void updateConsole();
	void serveIO();
  
	void calcStatiscs(Process* ptr);
  
	Processor* getLongestProcessor();
	Processor* getShortestProcessor();
  
public:
	Scheduler();
	bool startUp();
	void run();

	// loops on processorsGroup in O(n) and calls pushToRDY(ptr)
	// of the CPU with least expectedfinishTime
	// if the kind is by default set to any CPU
	bool moveToShortestRDY(Process* ptr, CPU_TYPE kind = NoCPU, bool moveToWaitingList = true);
	
	void moveToBLK(Process* ptr);
	void moveToTRM(Process* ptr);
	int getTimeStep() const;
	Process* createChild( int ct, Process* parent);
	//OverHeating Parameters
	int getOverHeatingPropability();
	int getOverHeatingTimeSteps();

	// takes a process pointer, and a DESTINATION (specific CPU type)
	bool migrate(Process*, CPU_TYPE);
	bool kill(std::string);
	//bool fork(std::string id, int AT, int CPUT);
	void simulation();

	int random(int upperbound = 100); //returns a value from 0 to 100
	~Scheduler();
};