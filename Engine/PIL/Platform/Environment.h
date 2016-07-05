#pragma once

#include "PIL/PILAPI.h"
#include "PIL/Collections/Dictionary.h"
#include "PIL/Collections/String.h"

enum EPlatform
{
	PLATFORM_WIN32,
	PLATFORM_MAC,
	PLATFORM_LINUX,
};

#define EPlatformToString(item) #item

/** 
 * Used to store and save environment variables
 */
class PIL_API VEnvironment
{

private:
	static VEnvironment* Instance;

	VDictionary<VString> Vars;

	/**
	 * Hashes the given string
	 */
	uint32 HashString(const VString& str);

public:

	static VEnvironment* GetInstance();

	VEnvironment();

	~VEnvironment();

	/**
	 * Puts and environment variable on the list
	 * if overwrite is true, a new value won't be added if another variable
	 * with the same key exists - except it will be overwritten. If false,
	 * the variable will not be added if a var with the same key already exists 
	 * and the value will remain unachanged.
	 */
	void Put(const VString& key, const char* val, bool overwrite = true);

	/**
	 * Gets the value of an environment variable and stores it in outVal
	 */
	bool Get(const VString& key, VString& outVal);

	/**
	 * Simply removes the variable with the given key
	 */
	bool Remove(const VString& key);

	/** 
	 * Searches the system environment variable for the given key
	 */
	static VString GetSystemEnvVar(const char* key);

	/**
	 * Returns which platform we are running on
	 */
	EPlatform GetPlatform();
};
