#include "RebTimer.h"

RebTimer::RebTimer()
{
	QueryPerformanceFrequency(&frequency);
}

void RebTimer::Start()
{
	QueryPerformanceCounter(&t1);
}

double RebTimer::GetCurrent()
{
	QueryPerformanceCounter(&t2);

	// compute and print the elapsed time in millisec
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	return elapsedTime;
}