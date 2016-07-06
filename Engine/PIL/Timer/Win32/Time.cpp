#include "PIL/Timer/Time.h"
#include <Windows.h>

struct VInternalTimeData
{
	LARGE_INTEGER Time;
	double Freq;
};

VTime::VTime()
	:Time(0.0f)
{
	InternalTime = new VInternalTimeData();

	LARGE_INTEGER clockFreq;

	QueryPerformanceFrequency(&clockFreq);
	InternalTime->Freq = double(clockFreq.QuadPart);		// Set frequency to seconds

	QueryPerformanceCounter(&InternalTime->Time);			// Take Time
}

void VTime::UpdateTime()
{
	LARGE_INTEGER newTime;
	 
	QueryPerformanceCounter(&newTime);

	double elapsed = double(newTime.QuadPart - InternalTime->Time.QuadPart) / InternalTime->Freq;		// Get difference in seconds

	// Set vars
	Time += elapsed;
	DeltaTime = elapsed;

	// Swap
	InternalTime->Time = newTime;
}