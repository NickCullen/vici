#pragma once

#include "PIL/PILAPI.h"

// Non-public abi struct
struct VInternalTimeData;

/**
 * Use to tick and keep track on how long 
 * has passed since the timer has started
 */
class PIL_API VTimer
{
private:
	VInternalTimeData* InternalTime;

	float TimeInSeconds;		// Time kept in seconds

	bool Paused;
public:

	VTimer();
	~VTimer();

	/**
	 * Advances the timer
	 */
	void Tick();

	/**
	 * Begins / restarts the timer
	 */
	void Begin();

	/**
	 * Pauses the timer, but DOESN'T reset
	 */
	void Pause();

	/**
	 * Resumes the timer from where it was last left
	 */
	void Resume();

	/**
	 * Stops and resets the timers
	 */
	void Stop();

	/**
	 * Simply sets TimeInSeconds to 0 and doesn't alter paused state
	 */
	void Reset();

	/**
	 * Returns the time in seconds
	 */
	inline float GetTimeInSeconds() { return TimeInSeconds; }
};