#include "UI.h"

void UI::print(std::string sr)
{
	std::cout << sr;
}

void UI::showStatus()
{
	std::cout << "Current Timestep: " << pScheduler->getTimeStep() << std::endl;
	std::cout << "------------------ RDY processes ------------------" << std::endl;
	pScheduler->printCPUs(); // here the scheduler should print the "processor " + number of the CPU
							 // and then make the CPU print it's type and it's ready list
	std::cout << "------------------ BLK processes ------------------" << std::endl;
	pScheduler->printBLK();  // this will print the number of processes in the BLK and their IDs
	std::cout << "------------------ RUN processes ------------------" << std::endl;
	pScheduler->printRUN();  //it will iterate on every CPU and make it print the process it has in the running state
	std::cout << "------------------ TRM processes ------------------" << std::endl;
	pScheduler->printTRM();  // this will print the number of processes terminated and then print them
}
