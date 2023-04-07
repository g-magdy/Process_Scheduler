#pragma once

enum ProcessState
{
	NEW,		// in the new list
	READY,		// in the ready list of a processor
	RUN,		// is bein run by a processor
	IO,			// in the block(I/O)
	TERM 		// is in the terminated list
};