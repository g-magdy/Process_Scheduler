#pragma once
#include <iostream>
#include "../DEFS.h"
#include "../Basic/Queue.h"

class Process
{
private:
	std::string ID;												 // the id of the process
	ProcessState currentState;									 
	CPU_TYPE handlingCPU;										 
	int ArrivalT;												 // arrival time
	int ResponseT;												 // response time
	int CPUT;													 // CPU time
	int FinishedCPUT;											 // finished CPU time
	int TerminationT;											 // termination time
	int TurnRoundT;												 // turn around time
	int WaitingT;												 // waiting time
	Queue<Pair<int,int>> IOList;								 // a queue to hold the IO requests of a process
	Process* myChild;											 // this may change to a list or be removed in the future *************
	int totalIOD;												 // to be printed in the output file
	int servedIODuration;										 // to track the (current IO request)'s finished time

public:															
	Process(std::string id, int inAT, int ct);					 // non-defult constructor
	Process(const Process& origin);								 // copy constructor		
	Process(std::string id);									 // this constructor is to be used in searching
	std::string getID() const;									 // getter to the id
																
	void setProcessState(ProcessState CS);						 // setter to the process state
	ProcessState getProcessState() const;						 // getter to the process state
																
	void setHandlingCPU(CPU_TYPE HCPU);							 // sets what type of CPU is handling the process
	CPU_TYPE getHandlingCPU() const;							 // getter to the type of CPU tha is handling the process
																
	int getArrivalT() const;									 // getter to the arrival time
																
	void setResponseT(int rt);									 // setter to the response time
	int getResponseT() const;									 // getter to the response time
																
	int getCPUT() const;										 // getter to the CPU time
																
	void updateFinishedCPUT(int n = 1);							 // increases the finished CPU time by a defult value of 1
	int getFinishedCPUT() const;								 // gets the finished CPU time
																
	void setTerminationT(int tt);								 // sets the termination time and then calculates the TurnRoundT and WaitingT
	int getTerminationT() const;								 // TT getter
																
	int getTurnRoundT() const;									 // total round time getter
																
	int getWaitingT() const;									 // watting time getter
																
	void pushIORquest(Pair<int,int>&);							 // Adds an IO request pair to the IOList 
	bool peekNextIOR(Pair<int, int>&);							 // Takes a peek on the first pair in the IOlist pairs
	bool popkNextIOR(Pair<int, int>&);							 // pops and returns the first pair in the IOlist pairs

	void incrementServedIODuration();
	int getServedIODuration();
	void resetServedIODuration();	

	Process* getMyChild();										 // gets the child of the Process
	void setMyChild(Process* ch);
	bool operator > (const Process& second);					 // compares between two processes in terms of cpu time
	bool operator < (const Process& second);					 // compares between two processes in terms of cpu time
	bool operator >= (const Process& second);					 // compares between two processes in terms of cpu time
	bool operator <= (const Process& second);					 // compares between two processes in terms of cpu time
};

std::ostream& operator << (std::ostream& out, const Process& p); //overload the inserstion operator to allow using "cout" directly on the Process objects
