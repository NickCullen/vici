#include "Editor.h"
#include "EngineMacros.h"
#include "Environment.h"
#include "FilePath.h"
#include <stdio.h>
#include <string>
#include "VString.h"

int main(int argc, const char** argv)
{
	const char* path = argv[0];
	VFilePath runningDirectory = VFilePath::TrimPath((char*)path);

	VString vpath = VEnvironment::GetSystemEnvVar("VICI_HOME");
	VFilePath vResPath = vpath + "Resources/";

	printf("Res = %s\n", (char*)vResPath);
	VEnvironment::GetInstance()->Put(ItemToString(FILE_EDITOR_DIRECTORY), vpath.c_str());
	VEnvironment::GetInstance()->Put(ItemToString(FILE_EDITOR_RESOURCE_DIRECTORY), vResPath);
	VEnvironment::GetInstance()->Put(ItemToString(FILE_RUNNING_DIRECTORY), runningDirectory);

	VEnvironment::GetInstance()->PrintEnvVars();

	VEditor editor;
	
	if (editor.Init(argc, argv))
	{
		return editor.Run();
	}
	else
		return -1;
}