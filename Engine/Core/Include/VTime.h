#ifndef VTIME_H
#define VTIME_H

#include "Singleton.h"
#include "CoreAPI.h"

#define _Time Singleton<VTime>::Instance()

/**
* Singleton class used to store delta time
* and keep track of time
*/

class CORE_API VTime : public Singleton<VTime>
{
	friend class Platform;
private:
	float Time; /**< The time since the program has started */

	float DeltaTime; /**< The delta time since last frame update */

	float TimeScale; /**< The time scale of program */
public:
	/**
	* Default constructor
	*/
	VTime();

	/**
	* Default destructor
	*/
	~VTime();

	/**
	* Getter for time since the program has started
	* @return Float representing time since program has started in seconds
	*/
	inline float GetTime(){ return this->Time; }

	/**
	* Getter for delta time between frames
	* @return Float representing delta time
	*/
	inline float GetDeltaTime(){ return this->DeltaTime; }

	/**
	* Getter for time scale (default 1.0f)
	* @return Float representing the scale of time
	*/
	inline float GetTimeScale(){ return this->TimeScale; }

	/**
	* Setter for time scale
	* @param scale The new time scale
	*/
	inline void SetTimeScale(float scale){ this->TimeScale = scale; }
};
#endif