#include "UI.h"

void UI::print(std::string sr)
{
	std::cout << sr;
}

char UI::getInput()
{
	char c;
	std::cin.get(c);
	return c;
}

UI::UI(Scheduler* SCDptr): pScheduler(SCDptr) {}

RunningMode UI::startUP()
{
	do
	{
		int mode = 0;
		std::cout << "------------ Select the Running Mode ------------\n";
		std::cout << " 1-Inter Active     2-Step by Step     3-Silent\n";
		std::cout << "\nYour choice: ";
		std::cin >> mode;
		if (mode == 1) return INTERACTIVE;
		else if (mode == 2) return STEPBYSTEP;
		else if (mode == 3)
		{
			std::cout << "\nSilent Mode.......  Simulation Starts.......\n";
			return SILENT;
		}
		std::cout << std::endl;
	} while (true);
}

void UI::showStatus(Processor** CPUList, int size, Queue<Process*>& BLKList, Queue<Process*>& TRMList)
{
	std::cout << "\nCurrent Timestep: " << pScheduler->getTimeStep() << std::endl;

	std::cout << "------------------ RDY processes ------------------" << std::endl;
	for (int i = 0; i < size; i++)
		CPUList[i]->print('l');
	
	std::cout << "------------------ BLK processes ------------------" << std::endl;
	std::cout << BLKList.size() << " BLK: ";
	BLKList.print();

	std::cout << "\n------------------ RUN processes ------------------" << std::endl;
	int runningCPUsCount = 0;
	for (int i = 0; i < size; i++)
		if (CPUList[i]->getCPUstate() == Busy) runningCPUsCount++;
	std::cout << runningCPUsCount << " RUN: ";
	for (int i = 0, j = 0; i < size; i++)
		if (CPUList[i]->getCPUstate() == Busy)
		{
			j++;
			CPUList[i]->print('r');
			if (j < runningCPUsCount) std::cout << ", ";
		}

	std::cout << "\n------------------ TRM processes ------------------" << std::endl;
	std::cout << TRMList.size() << " TRM: ";
	TRMList.print();

	std::cout << std::endl;
}

std::string UI::getInputfilename()
{
	std::string name;
	std::cout << "WELCOME TO OUR PROCESS SCHEDULER, FRIEND :)\n\n";
	std::cout << "Enter the input-file name (without .txt extension) or enter 'd' for default: ";
	std::cin >> name;

	// default
	if (name.compare("d") == 0)
		name = "sample1";

	return name;
}
