#include "Editor.h"
#include "EngineMacros.h"
#include "Environment.h"
#include "FilePath.h"
#include <stdio.h>
#include <string>

void TrimPath(const char* path)
{
	int len = strlen(path);
	char* currentChar = (char*)&path[len];
	while(*currentChar != '\\' && *currentChar != '/')
	{
		*currentChar = '\0';
		currentChar--;
	}
}

int main(int argc, const char** argv)
{
	const char* path = argv[0];
	TrimPath(path);

	const char* vpath = VEnvironment::GetSystemEnvVar("VICI_HOME");

	printf("Executable = %s\n", argv[0]);

	// Setup environment
	VEnvironment::GetInstance()->Put(ItemToString(FILE_EDITOR_DIRECTORY), argv[0], true);
	VEnvironment::GetInstance()->Put(ItemToString(FILE_RUNNING_DIRECTORY), argv[0], true);
	VEnvironment::GetInstance()->Put("lol", "mylol", false);

	

	VEnvironment::GetInstance()->Remove("lol");

	const char* mylol = VEnvironment::GetInstance()->Get("lol");


	VEditor editor;
	
	if (editor.Init(argc, argv))
	{
		return editor.Run();
	}
	else
		return -1;
}