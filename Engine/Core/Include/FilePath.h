#pragma once

#include "CoreAPI.h"
#include "VString.h"

/**
 * Defines where the filepath
 * should be located
 */
enum EFileLocation
{
	FILE_RUNNING_DIRECTORY,
	FILE_EDITOR_DIRECTORY
};

/**
 * Wrapper around VString that will always
 * contain a absolute path (platform friendly)
 * to the specified file
 */
class CORE_API VFilePath
{
private:
	EFileLocation Location;	// Where this file is located

	VString Path;	// The absolute path

	/**
	 * Prefixes the location of Location enum
	 * onto Path
	 */
	void PrefixLocation();

public:
	VFilePath(const VString& relativeFilePath, EFileLocation location = FILE_RUNNING_DIRECTORY);

	~VFilePath();

	/**
	* Makes sure the given path is platform friendly
	*/
	static void EnsurePathFriendly(char* path);
};