#include "Scheduler.h"

Scheduler::Scheduler() : processorsGroup(nullptr), currentTimeStep(0), pUI(nullptr)
{
}

int Scheduler::random(int upperbound) const
{
	std::srand(time(NULL));
	return std::rand() % upperbound;
}

int Scheduler::getTimeStep() const
{
    return currentTimeStep;
}

void Scheduler::printCPUs() const
{
}

void Scheduler::printBLK() const
{
}

void Scheduler::printRUN() const
{
}

void Scheduler::printTRM() const
{
}

Scheduler::~Scheduler()
{
}
