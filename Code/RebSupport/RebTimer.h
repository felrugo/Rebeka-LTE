#ifndef REBTIMER_H
#define REBTIMER_H

#include <Windows.h>

class RebTimer
{
	LARGE_INTEGER frequency;        // ticks per second
	LARGE_INTEGER t1, t2;           // ticks
	double elapsedTime;

public:
	RebTimer();

	double GetCurrent();

	void Start();
};




#endif