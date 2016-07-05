#include "PIL/FileSystem/FilePath.h"
#include "PIL/Platform/Environment.h"
#include "PIL/Collections/String.h"
#ifdef VICI_WINDOWS
#define VALID_SLASH '\\'
#define INVALID_SLASH '/'
#else
#define VALID_SLASH '/'
#define INVALID_SLASH '\\'
#endif

#include <stdlib.h>

#define ItemToString(item) #item

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

VFilePath::~VFilePath()
{
	
}

void VFilePath::PrefixLocation()
{

	switch (Location)
	{
	case FILE_RUNNING_DIRECTORY:
		VEnvironment::GetInstance()->Get(ItemToString(FILE_RUNNING_DIRECTORY), Path);
		break;
	case FILE_EDITOR_DIRECTORY:
		VEnvironment::GetInstance()->Get(ItemToString(FILE_EDITOR_DIRECTORY), Path);
		break;
	case FILE_EDITOR_RESOURCE_DIRECTORY:
		VEnvironment::GetInstance()->Get(ItemToString(FILE_EDITOR_RESOURCE_DIRECTORY), Path);
		break;
	default:
		VEnvironment::GetInstance()->Get(ItemToString(FILE_RUNNING_DIRECTORY), Path);	// Assume running directory
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

VFilePath VFilePath::operator+(const VString& str) const
{
	return VFilePath(Path + str);
}

VString VFilePath::GetDirectory() const
{
	VString ret = Path;
	size_t indexOf = ret.find_last_of(VALID_SLASH);
	ret.erase(indexOf+1);
	return ret;
}