#include "Process.h"

Process::Process(std::string id, int inAT, int ct) : ArrivalT(inAT), ID(id), CPUT(ct)
{
	ResponseT = TerminationT = TurnRoundT = -1; // they are not givn real values yet
	totalIOD = FinishedCPUT = servedIODuration = 0;
	WaitingT = 0;
	currentState = NEW;
	handlingCPU = NoCPU;
	myChild = mySecondChild = myParent = nullptr;
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
	myChild = mySecondChild = myParent = nullptr;      //what should I set this to ?
	servedIODuration = 0;
}

Process::Process(std::string id): ID(id), servedIODuration(0)
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
	//WaitingT = TurnRoundT - CPUT;
	// what if the process was killed or an orphan which his parent was terminated ?
	// the turn around time in this case will be smaller than CPUT (it did not finish execution)
	WaitingT = tt - ArrivalT - FinishedCPUT; // tt is the current time step
	WaitingT = (WaitingT > 0) ? WaitingT : 0;
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

int Process::getTotalIOD() {
	return totalIOD;
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
	return true;
}

bool Process::popkNextIOR(Pair<int, int>& P)
{
	if (IOList.isEmpty())
		return false;

	IOList.pop(P);
}

void Process::incrementServedIODuration()
{
	servedIODuration++;
}

int Process::getServedIODuration()
{
	return servedIODuration;
}

void Process::resetServedIODuration()
{
	servedIODuration = 0;
}

void Process::incrementTotalIOD(int a)
{
	totalIOD += a;
}

Process* Process::getMyChild()
{
	return myChild;
}

Process* Process::getMySecondChild()
{
	return mySecondChild;
}

void Process::setMyChild(Process* ch)
{
	myChild = ch;
}

void Process::setMySecondChild(Process* ch2)
{
	mySecondChild = ch2;
}

Process* Process::getMyParent()
{
	return myParent;
}

void Process::setMyParent(Process* parent)
{
	myParent = parent;
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
