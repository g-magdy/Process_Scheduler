#pragma once
#include <iostream>
#include "../DEFS.h"
class UI
{
private:
	//Scheduler* pScheduler;        // A Pointer to the Scheduler

public:
	void print(std::string sr);     // Prints a string given to it with no extra spaces or "endl"
	RunninMode startUP();			//this will be implemented in phase 2
	void showStatus();			//this might be int the private if the UI is the one responsble
									// for running the console
};
