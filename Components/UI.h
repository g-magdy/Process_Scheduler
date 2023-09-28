#pragma once
#include <iostream>
#include "../DEFS.h"
#include "../Scheduler.h"

class Scheduler;

class UI
{						
private:
	Scheduler* pScheduler;
public:		
	UI(Scheduler*);
	RunningMode startUP();			     //this will be implemented in phase 2

	void showStatus(Processor** CPUList, int size, Queue<Process*>& BLKList, Queue<Process*>& TRMList);
									     
	void print(std::string sr);          // Prints a string given to it with no extra spaces or "endl"
	char getInput();

	std::string getInputfilename();
									     
	/*template<typename T>			     
	void print(T* ob);*/				     
};

//template<typename T>
//inline void UI::print(T* ob)
//{
//	std::cout << *ob;
//}
