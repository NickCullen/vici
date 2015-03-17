#ifndef PLATFORM_H
#define PLATFORM_H

#ifndef NULL
#define NULL 0
#endif

#include "PlatformDefinitions.h"
#include "Singleton.h"

/**
* Singleton class containing platform specific functions
* such as correcting path strings and logging strings
* Can be accessed by the _Platform-> macro defined in Vici.h
*/

class Platform : public Singleton<Platform>
{
private:
	char _cwd[BUFF_LEN]; /**< Contains the current working directory of the program */

public:
	/**
	* Default constructor
	*/
	Platform();

	/**
	* Default destructor
	*/
	~Platform();

	/**
	* Logs a string to the given output
	* @param fmt Format of string like printf
	*/
	void LogString(const char* fmt, ...);

	/**
	* Returns the time in milliseconds
	* @return double representing time in milliseconds
	*/
	double GetTime();

	/**
	* Enter the platforms game loop
	* @param v Pointer to the vici instance
	*/
	void EnterLoop(class Vici* v);

	/**
	* Turns a path in c style string format into a platform
	* corrent and sensible path (i.e. converts forward slashes
	* to backslashes on windows machines)
	* @param file The file path
	* @return returns the same pointer 
	*/
	const char* Pathify(const char* file);

	/**
	* Returns the current working directory - note that classes calling this function
	* should not attempt to delete or modify this pointer
	* @return A char pointer (C String) containing the current working directory
	*/
	inline char* GetCwd() { return _cwd; }

	/**
	* Called before any vici function and set by the programs
	* main function. Will take the argument argv[0] (the executable
	* file path and construct it)
	* @param executable_path The argument argv[0] passed into main
	* @param trim_end Boolean to set to true to remove the executable name from the end of the executable_path
	*/
	void SetCwd(const char* executable_path, bool trim_end = false);
};

#endif