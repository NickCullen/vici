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

	/**
	* The time since program has run
	*/
	static float _time;

	/**
	* The delta time since last frame
	*/
	static float _delta_time;
};
#endif