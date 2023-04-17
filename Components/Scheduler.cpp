#include "Scheduler.h"

Scheduler::Scheduler() : processorsGroup(nullptr), currentTimeStep(0), pUI(nullptr)
{
}

void Scheduler::startUp()
{
}

bool Scheduler::run()
{
	return false;
}

void Scheduler::moveToBLK()
{
}

void Scheduler::moveToTRM()
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

Process* Scheduler::createChild(int)
{
	return nullptr;
}

bool Scheduler::migrate(Process*, CPU_TYPE)
{
	return false;
}

bool Scheduler::kill(std::string)
{
	return false;
}

Scheduler::~Scheduler()
{
}

void Scheduler::readInputFile()
{
}

void Scheduler::createOutputFile()
{
}

void Scheduler::update()
{
}

Process* Scheduler::createProcess(std::string, int, int)
{
	return nullptr;
}

Processor* Scheduler::createCPU(CPU_TYPE)
{
	return nullptr;
}

bool Scheduler::steal()
{
	return false;
}

bool Scheduler::kill()
{
	return false;
}
