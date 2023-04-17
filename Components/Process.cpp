#include "Process.h"

Process::Process(std::string id, int inAT, int ct) : ArrivalT(inAT), ID(id), CPUT(ct)
{
	ResponseT = TerminationT = TurnRoundT = WaitingT = -1; // they are not givn real values yet
	totalIOD = FinishedCPUT = 0;
	currentState = NEW;
	handlingCPU = NoCPU;
	myChild = nullptr;
}

Process::Process(const Process& origin)
{
	ID = origin.ID;
	currentState = origin.currentState;
	handlingCPU = origin.handlingCPU;
	ArrivalT = origin.ArrivalT;
	ResponseT = origin.ResponseT;
	CPUT = origin.CPUT;
	FinishedCPUT = origin.FinishedCPUT;
	TerminationT = origin.TerminationT;
	TurnRoundT = origin.TurnRoundT;
	WaitingT = origin.WaitingT;
	IOList = origin.IOList;
	myChild = nullptr;      //what should I set this to ?
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

int Process::getArrivalT() const
{
	return ArrivalT;
}

void Process::setResponseT(int rt)
{
	if(ResponseT == -1)
		ResponseT = rt;
}

int Process::getResponseT() const
{
	return ResponseT;
}

int Process::getCPUT() const
{
	return CPUT;
}

void Process::updateFinishedCPUT(int n)
{
	FinishedCPUT += n;
}

int Process::getFinishedCPUT() const
{
	return FinishedCPUT;
}

void Process::setTerminationT(int tt)
{
	TerminationT = tt;
	TurnRoundT = TerminationT - ArrivalT;
	WaitingT = TurnRoundT - CPUT;
}

int Process::getTerminationT() const
{
	return TerminationT;
}

int Process::getTurnRoundT() const
{
	return TurnRoundT;
}

int Process::getWaitingT() const
{
	return WaitingT;
}

void Process::pushIORquest(Pair<int,int>& ioPair)
{
	IOList.push(ioPair);
}

bool Process::peekNextIOR(Pair<int, int>& P)
{
	if (IOList.isEmpty())
		return false;

	P = IOList.Front();
}

bool Process::popkNextIOR(Pair<int, int>& P)
{
	if (IOList.isEmpty())
		return false;

	IOList.pop(P);
}

Process* Process::getMyChild()
{
	return myChild;
}

bool Process::operator>(const Process& second)
{
	return (CPUT > second.CPUT);
}

bool Process::operator<(const Process& second)
{
	return CPUT < second.CPUT;
}

bool Process::operator>=(const Process& second)
{
	return CPUT >= second.CPUT;
}

bool Process::operator<=(const Process& second)
{
	return CPUT <= second.CPUT;
}

std::ostream& operator<<(std::ostream& out, const Process& p)
{
	out << p.getID();
	return out;
}
