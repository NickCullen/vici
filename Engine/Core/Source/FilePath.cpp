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


VFilePath::VFilePath(const VString& relativeFilePath, EFileLocation location)
	: Location(location)
{
	EnsurePathFriendly(relativeFilePath);
	PrefixLocation();
	Path = Path + relativeFilePath;
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

void VFilePath::EnsurePathFriendly(char* path)
{
	int len = strlen(path);
	for (int i = 0; i < len; i++)
	{
		if (path[i] == INVALID_SLASH)
			path[i] = VALID_SLASH;
	}
}