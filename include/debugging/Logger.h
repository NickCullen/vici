#ifndef V_LOGGER
#define V_LOGGER

/* Includes */
#include "Singleton.h"

/**
* Singleton class used to log commands 
* Can be accessed by using the _Logger macro 
* defined in vici.h
*/

class Logger : public Singleton<Logger>
{
private:

public:
	/**
	* Default constructor
	*/
	Logger();

	/**
	* Default destructor
	*/
	~Logger();

	/**
	* Logs a string to the console output
	* or to file if needed
	*/
	void Log(const char* fmt, ...);
};

#endif