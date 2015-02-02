#ifndef V_TIME
#define V_TIME

/**
* Static class used to store delta time
* and keep track of certain time
*/

class VTime
{
private:

public:
	/**
	* Unused constructor (static class) 
	*/
	VTime(){};

	/**
	* Unused destructor (static class)
	*/
	~VTime(){};

	static float _time; /**< The time since the program has started */

	static float _delta_time; /**< The delta time since last frame update */

	static float _time_scale; /**< The time scale of program */
};
#endif