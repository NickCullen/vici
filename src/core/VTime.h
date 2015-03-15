#ifndef V_TIME
#define V_TIME

#include "Singleton.h"

/**
* Static class used to store delta time
* and keep track of certain time
*/

class VTime : public Singleton<VTime>
{
private:
	float _time; /**< The time since the program has started */

	float _delta_time; /**< The delta time since last frame update */

	float _time_scale; /**< The time scale of program */
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
	inline float Time(){ return _time; }

	/**
	* Setter for time
	* @param time The new time
	*/
	inline void SetTime(float time) { _time = time; }

	/**
	* Getter for delta time between frames
	* @return Float representing delta time
	*/
	inline float DeltaTime(){ return _delta_time; }

	/**
	* Setter for delta time
	* @param dt The new delta time
	*/
	inline void SetDeltaTime(float dt) { _delta_time = dt; }

	/**
	* Getter for time scale (default 1.0f)
	* @return Float representing the scale of time
	*/
	inline float TimeScale(){ return _time_scale; }

	/**
	* Setter for time scale
	* @param scale The new time scale
	*/
	inline void SetTimeScale(float scale){ _time_scale = scale; }
};
#endif