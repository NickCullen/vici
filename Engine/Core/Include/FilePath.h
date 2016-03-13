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

	FILE_EDITOR_DIRECTORY,
	FILE_EDITOR_RESOURCE_DIRECTORY
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
	VFilePath(const VString& relativeFilePath, EFileLocation location);
	VFilePath(const VString& relativeFilePath);
	VFilePath(const char* relativeFilePath);
	VFilePath(char* relativeFilePath);

	~VFilePath();

	/**
	* Makes sure the given path is platform friendly
	*/
	static const char* EnsurePathFriendly(char* path);

	/**
	 * Trims the file path so that the filename (and extension) is 
	 * removed from the string, leaving only its absolute path to the directory
	 */
	static const char* TrimPath(char* path);

	// Data access
	const char* GetString() const;

	// Cast operators
	operator const char*() const;
	operator char*();

	/**
	 * Returns the full path of the directory this
	 * file is contained in
	 */
	VString GetDirectory() const;
};