#include "FilePath.h"
#include "EngineMacros.h"
#include "Environment.h"
#include <string>
#ifdef VICI_WINDOWS
#define VALID_SLASH '\\'
#define INVALID_SLASH '/'
#else
#define VALID_SLASH '/'
#define INVALID_SLASH '\\'
#endif

#include <stdlib.h>


VFilePath::VFilePath(const VString& relativeFilePath, EFileLocation location)
	: Location(location)
{
	EnsurePathFriendly((char*)relativeFilePath.c_str());
	PrefixLocation();
	Path = Path + relativeFilePath;
}

VFilePath::VFilePath(const VString& relativeFilePath)
{
	EnsurePathFriendly((char*)relativeFilePath.c_str());
	Path = relativeFilePath;
}

VFilePath::VFilePath(const char* relativeFilePath)
{
	EnsurePathFriendly((char*)relativeFilePath);
	Path = relativeFilePath;
}

VFilePath::VFilePath(char* relativeFilePath)
{
	EnsurePathFriendly(relativeFilePath);
	Path = relativeFilePath;
}

VFilePath::~VFilePath()
{
	
}

void VFilePath::PrefixLocation()
{

	switch (Location)
	{
	case FILE_RUNNING_DIRECTORY:
		Path = VEnvironment::GetInstance()->Get(ItemToString(FILE_RUNNING_DIRECTORY));
		break;
	case FILE_EDITOR_DIRECTORY:
		Path = VEnvironment::GetInstance()->Get(ItemToString(FILE_EDITOR_DIRECTORY));
		break;
	case FILE_EDITOR_RESOURCE_DIRECTORY:
		Path = VEnvironment::GetInstance()->Get(ItemToString(FILE_EDITOR_RESOURCE_DIRECTORY));
		break;
	default:
		Path = VEnvironment::GetInstance()->Get(ItemToString(FILE_RUNNING_DIRECTORY));	// Assume running directory
		break;
	}

	
}

const char* VFilePath::EnsurePathFriendly(char* path)
{
	size_t len = strlen(path);
	for (size_t i = 0; i < len; i++)
	{
		if (path[i] == INVALID_SLASH)
			path[i] = VALID_SLASH;
	}
	return path;
}

const char* VFilePath::TrimPath(char* path)
{
	size_t len = strlen(path);
	char* currentChar = &path[len];
	while (*currentChar != '\\' && *currentChar != '/')
	{
		*currentChar = '\0';
		currentChar--;
	}
	return path;
}

const char* VFilePath::GetString() const
{
	return Path.c_str();
}

VFilePath::operator const char *() const
{
	return (const char*)Path.c_str();
}

VFilePath::operator char *()
{
	return (char*)Path.c_str();
}

VString VFilePath::GetDirectory() const
{
	VString ret = Path;
	size_t indexOf = ret.find_last_of(VALID_SLASH);
	ret.erase(indexOf+1);
	return ret;

	/*VString dirPath = Path;
	uint32 deducted = 0;
	for (int32 i = (int32)dirPath.length(); i > 0; i--)
	{
		if (dirPath[i] != VALID_SLASH)
		{
			dirPath[i] = '\0';
			deducted++;
		}
		else
			break;
	}
	dirPath.SetLength(dirPath.length() - deducted);
	return dirPath;*/
}