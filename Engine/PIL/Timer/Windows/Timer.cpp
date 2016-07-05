#include "PIL/Timer/Timer.h"
#include <Windows.h>

struct VInternalTimeData
{
	LARGE_INTEGER Time;
	double Freq;
};

VTimer::VTimer()
	: TimeInSeconds(0.0f),
	Paused(true)
{
	InternalTime = new VInternalTimeData();

	LARGE_INTEGER clockFreq;

	QueryPerformanceFrequency(&clockFreq);
	InternalTime->Freq = double(clockFreq.QuadPart);		// Set frequency to seconds
}

VTimer::~VTimer()
{
	delete(InternalTime);
}

void VTimer::Tick()
{
	if (!Paused)
	{
		LARGE_INTEGER newTime;

		QueryPerformanceCounter(&newTime);

		double elapsed = double(newTime.QuadPart - InternalTime->Time.QuadPart) / InternalTime->Freq;		// Get difference in seconds
																											// Set vars
		TimeInSeconds += elapsed;

		// Swap
		InternalTime->Time = newTime;
	}
}

void VTimer::Begin()
{
	QueryPerformanceCounter(&InternalTime->Time);			// Take Time

	TimeInSeconds = 0.0f;	// Reset
	Paused = false;
}

void VTimer::Pause()
{
	Paused = true;
}

void VTimer::Resume()
{
	Paused = false;
}

void VTimer::Stop()
{
	TimeInSeconds = 0.0f;
	Paused = true;
}

void VTimer::Reset()
{
	TimeInSeconds = 0.0f;
}