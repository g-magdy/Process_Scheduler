#include "Process.h"

Process::Process(std::string id, int inAT, int ct) : AT(inAT), ID(id), CT(ct)
{
	RT = TT = TRT = WT = -1; // they are not givn real values yet
	FCT = 0;
	currentState = NEW;
	handlingCPU = NoCPU;
	myChild = nullptr;
}

Process::Process(const Process& origin)
{
	ID = origin.ID;
	currentState = origin.currentState;
	handlingCPU = origin.handlingCPU;
	AT = origin.AT;
	RT = origin.RT;
	CT = origin.CT;
	FCT = origin.FCT;
	TT = origin.TT;
	TRT = origin.TRT;
	WT = origin.WT;
	IOList = origin.IOList;
	myChild = nullptr;      //what should I set this to ?
}

Process::Process()
{
}

std::string Process::getID() const
{
	return ID;
}

void Process::setProcessState(ProcessState CS)
{
	currentState = CS;
}

ProcessState Process::getProcessState() const
{
	return currentState;
}

void Process::setHandlingCPU(CPU_TYPE HCPU)
{
	handlingCPU = HCPU;
}

CPU_TYPE Process::getHandlingCPU() const
{
	return handlingCPU;
}

int Process::getAT() const
{
	return AT;
}

void Process::setRT(int rt)
{
	RT = rt;
}

int Process::getRT() const
{
	return RT;
}

int Process::getCT() const
{
	return CT;
}

void Process::updateFCT(int n )
{
	FCT += n;
}

int Process::getFCT() const
{
	return FCT;
}

void Process::setTT(int tt)
{
	TT = tt;
	TRT = TT - AT;
	WT = TRT - CT;
}

int Process::getTT() const
{
	return TT;
}

int Process::getTRT() const
{
	return TRT;
}

int Process::getWT() const
{
	return WT;
}

Process* Process::getMyChild()
{
	return myChild;
}

bool Process::operator>(const Process& second)
{
	return (CT > second.CT);
}

bool Process::operator<(const Process& second)
{
	return CT < second.CT;
}

bool Process::operator>=(const Process& second)
{
	return CT >= second.CT;
}

bool Process::operator<=(const Process& second)
{
	return CT <= second.CT;
}
