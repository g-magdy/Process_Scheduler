#pragma once
#include <iostream>
#include "../DEFS.h"
#include "../Basic/Queue.h"

class Process
{
private:
	std::string ID;					// the id of the process
	ProcessState currentState;
	CPU_TYPE handlingCPU;
	int AT;						// arrival time
	int RT;						// response time
	int CT;						// CPU time
	int FCT;					// finished CPU time
	int TT;						// termination time
	int TRT;					// turn around time
	int WT;						// waiting time
	Queue<Pair<int>> IOList;    // a queue to hold the IO requests of a process
	Process* myChild;			// this may change to a list or be removed in the future *************

public:
	Process(std::string id, int inAT, int ct);    // non-defult constructor
	Process(const Process& origin);				  // copy constructor
	Process();									  //default argument constructor
	std::string getID() const;					  // getter to the id

	void setProcessState(ProcessState CS);		  // setter to the process state
	ProcessState getProcessState() const;		  // getter to the process state

	void setHandlingCPU(CPU_TYPE HCPU);			  // sets what type of CPU is handling the process
	CPU_TYPE getHandlingCPU() const;              // getter to the type of CPU tha is handling the process

	int getAT() const;							  // getter to the arrival time

	void setRT(int rt);							  // setter to the response time
	int getRT() const;							  // getter to the response time

	int getCT() const;							  // getter to the CPU time

	void updateFCT(int n = 1);					  // increases the finished CPU time by a defult value of 1
	int getFCT() const;							  // gets the finished CPU time

	void setTT(int tt);							  // sets the termination time and then calculates the TRT and WT
	int getTT() const;							  // TT getter

	int getTRT() const;							  // total round time getter

	int getWT() const;							  // watting time getter

	Process* getMyChild();						  // gets the child of the Process

	bool operator > (const Process& second);      // compares between two processes in terms of cpu time
	bool operator < (const Process& second);	  // compares between two processes in terms of cpu time
	bool operator >= (const Process& second);	  // compares between two processes in terms of cpu time
	bool operator <= (const Process& second);	  // compares between two processes in terms of cpu time
};

