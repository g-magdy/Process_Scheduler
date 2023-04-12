#pragma once

enum ProcessState
{
	NEW,		// in the new list
	READY,		// in the ready list of a processor
	RUN,		// is bein run by a processor
	Blocked,	// is in the Blocked list waiting its turn for IO
	IO,			// is being served the IO it requested
	TERM 		// is in the terminated list
};

enum CPU_TYPE
{
	FCFS_T,
	SJF_T,
	RR_T,
	NoCPU
};

enum CPU_STATE {
	Busy,		//MEAN the procssor is excuting a process
	IDLE		//mean the reay list is empty 
};

enum RunninMode
{
	Interactive,
	StepByStep,
	Silent
};

template<typename T>
struct Pair
{
	T first;
	T second;
};