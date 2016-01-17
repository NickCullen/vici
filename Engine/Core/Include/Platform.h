#ifndef PLATFORM_H
#define PLATFORM_H

#ifndef NULL
#define NULL 0
#endif

#include "CoreAPI.h"
#include "PlatformDefinitions.h"
#include "Singleton.h"

/* Quick access macro */
#define _Platform Singleton<Platform>::Instance()

/**
* Singleton class containing platform specific functions
* such as correcting path strings and logging strings
* Can be accessed by the _Platform-> macro defined in Vici.h
*/

class CORE_API Platform : public Singleton<Platform>
{
private:
	char _cwd[BUFF_LEN]; /**< Contains the current working directory of the program */

	/**
	* Returns the time in milliseconds - not public anymore should use (_Time->GetTime())
	* @return double representing time in milliseconds
	*/
	double GetTime();

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
	* Turns a path in c style string format into a platform
	* corrent and sensible path (i.e. converts forward slashes
	* to backslashes on windows machines)
	* @param file The file path
	* @return returns the same pointer
	*/
	std::string& Pathify(std::string& file);

	/**
	* Returns the current working directory - note that classes calling this function
	* should not attempt to delete or modify this pointer
	* @return A char pointer (C String) containing the current working directory
	*/
	inline char* GetCwd() { return _cwd; }

	/**
	* Appends the string to the cwd and returns it
	* @param append The string to append to cwd
	* @return reference to input string
	*/
	std::string& GetFullPath(std::string& append);

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