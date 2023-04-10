/*
* In this file we will collect all of our random little coding ideas
* and functions and non complete implementations
* NO JUDGEMENT - BRAINSTORMING
*/

// ===============
//      ENUMS
// ===============

enum PROCESS_STATE
{
    NEW,
    READY,
    RUNNING,
    BLOCKED,
    TERMINATED,
    ORPHAN
};

enum CPU_TYPE
{
    FCFS,
    SJF,
    RR
};

enum CPU_STATE
{
    IDLE,
    BUSY
};

//#include <ctime>
//int randomPercent() //returns a value from 0 to 100
//{
//    srand(time(NULL));
//    return rand() % 101;
//}