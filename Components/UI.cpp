#include "UI.h"
#include <windows.h>
enum colors
{
	black,
	blue,
	green,
	aqua,
	red,
	purple,
	yellow,
	white,
	gray
};
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
	HANDLE console_color;
	colors  textColor = white;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	do
	{
		int mode = 0;
		textColor = red;
		SetConsoleTextAttribute(console_color,textColor);
		std::cout << "\n------------ Select the Running Mode ------------\n";
		textColor = aqua;
		SetConsoleTextAttribute(console_color, textColor);
		std::cout << " 1-Inter Active     2-Step by Step     3-Silent\n";
		textColor = yellow;
		SetConsoleTextAttribute(console_color, textColor);
		std::cout << "\nYour choice: ";
		std::cin >> mode;
		if (mode == 1) return INTERACTIVE;
		else if (mode == 2) return STEPBYSTEP;
		else if (mode == 3)
		{
			textColor = gray;
			SetConsoleTextAttribute(console_color, textColor);
			std::cout << "\nSilent Mode.......  Simulation Starts.......\n";
			return SILENT;
		}
		std::cout << std::endl;
	} while (true);
}

void UI::showStatus(Processor** CPUList, int size, Queue<Process*>& BLKList, Queue<Process*>& TRMList)
{
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	colors backgroundColor = black, textColor =red;
	SetConsoleTextAttribute(console_color, textColor);
	std::cout << "\nCurrent Timestep: " << pScheduler->getTimeStep() << std::endl;
	textColor = green;
	SetConsoleTextAttribute(console_color, textColor);
	std::cout << "------------------ RDY processes ------------------" << std::endl;
	for (int i = 0; i < size; i++)
		CPUList[i]->print('l');


	textColor = red;
	SetConsoleTextAttribute(console_color, textColor);
	std::cout << "------------------ BLK processes ------------------" << std::endl;
	std::cout << BLKList.size() << " BLK: ";
	BLKList.print();


	textColor = blue;
	SetConsoleTextAttribute(console_color, textColor);
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
	textColor = yellow;
	SetConsoleTextAttribute(console_color, textColor);
	std::cout << "\n------------------ TRM processes ------------------" << std::endl;
	std::cout << TRMList.size() << " TRM: ";
	TRMList.print();
	textColor = white;
	SetConsoleTextAttribute(console_color, textColor);
	std::cout << std::endl;
}

std::string UI::getInputfilename()
{
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	colors textColor=white;
	std::string name;
	SetConsoleTextAttribute(console_color,BACKGROUND_INTENSITY|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
	std::cout << "\nWELCOME TO OUR PROCESS SCHEDULER, FRIEND :)\n\n";
	textColor = yellow;
	SetConsoleTextAttribute(console_color, textColor);
	std::cout << "Enter the input-file name (without .txt extension) or enter 'd' for default: ";
	std::cin >> name;

	// default
	if (name.compare("d") == 0)
		name = "sample1";

	return name;
}
