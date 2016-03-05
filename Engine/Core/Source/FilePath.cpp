#include "FilePath.h"
#include <stdio.h>  /* defines FILENAME_MAX */
#include <string>
#ifdef VICI_WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#define VALID_SLASH '\\'
#define INVALID_SLASH '/'
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#define VALID_SLASH '/'
#define INVALID_SLASH '\\'
#endif

#include <stdlib.h>


VFilePath::VFilePath(const VString& relativeFilePath, EFileLocation location)
	: Location(location)
{
	EnsurePathFriendly(relativeFilePath);
	PrefixLocation();
	Path = Path + relativeFilePath;
}

VFilePath::VFilePath(const VString& relativeFilePath)
{
	EnsurePathFriendly(relativeFilePath);
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
	char buff[FILENAME_MAX];
	if (GetCurrentDir(buff, sizeof(buff)))
	{
		printf("buff = %s\n", buff);
		Path = buff;
	}
}

const char* VFilePath::EnsurePathFriendly(char* path)
{
	int len = strlen(path);
	for (int i = 0; i < len; i++)
	{
		if (path[i] == INVALID_SLASH)
			path[i] = VALID_SLASH;
	}
	return path;
}

const char* VFilePath::TrimPath(char* path)
{
	int len = strlen(path);
	char* currentChar = &path[len];
	while (*currentChar != '\\' && *currentChar != '/')
	{
		*currentChar = '\0';
		currentChar--;
	}
	return path;
}


VFilePath::operator const char *()
{
	return (const char*)Path;
}

VFilePath::operator char *()
{
	return (char*)Path;
}