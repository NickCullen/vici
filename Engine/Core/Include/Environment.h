#pragma once

#include "CoreAPI.h"
#include "Singleton.h"
#include "Hash.h"
#include "VString.h"

/** 
 * Used to store and save environment variables
 */
class CORE_API VEnvironment : public VSingleton<VEnvironment>
{
	struct VEnvVar
	{
		VEnvVar* Next;
		VHash Key;
		VString Value;
	};

private:
	VEnvVar* Head;	// First variable
public:

	VEnvironment();

	~VEnvironment();

	/**
	 * Puts and environment variable on the list
	 * if overwrite is true, a new value won't be added if another variable
	 * with the same key exists - except it will be overwritten. If false,
	 * the variable will not be added if a var with the same key already exists 
	 * and the value will remain unachanged.
	 */
	bool Put(VHash key, const char* val, bool overwrite = true);

	/**
	 * Gets the value of an environment variable
	 */
	const char* Get(VHash key);

	/**
	 * Simply removes the variable with the given key
	 */
	bool Remove(VHash key);

	/** 
	 * Searches the system environment variable for the given key
	 */
	static const char* GetSystemEnvVar(const char* key);

	/**
	 * Prints env vars
	 */
	void PrintEnvVars();
};