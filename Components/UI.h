#pragma once
#include <iostream>
#include "../DEFS.h"
#include "../Scheduler.h"

class Scheduler;

class UI
{
private:
	Scheduler* pScheduler;			// A Pointer to the Scheduler

public:
	RunningMode startUP();			//this will be implemented in phase 2
	void showStatus();				//this might be int the private if the UI is the one responsble
									// for running the console
	void print(std::string sr);     // Prints a string given to it with no extra spaces or "endl"

	template<typename T>
	void print(T* ob);				// Prints a string given to it with no extra spaces or "endl"
};

template<typename T>
inline void UI::print(T* ob)
{
	std::cout << *ob;
}
