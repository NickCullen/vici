#include "ViciEditor/Editor.h"
#include "Core/EngineIncludes.h"
#include <stdio.h>

int main(int argc, const char** argv)
{
	// Setup running directory path
	VFilePath runningDirectory = VFilePath::TrimPath((char*)argv[0]);
	VEnvironment::GetInstance()->Put(ItemToString(FILE_RUNNING_DIRECTORY), runningDirectory);

	// SETUP paths for VICI_EDITOR editor builds
#ifdef VICI_EDITOR
	VFilePath viciHome = VEnvironment::GetInstance()->GetSystemEnvVar("VICI_HOME");

	VEnvironment::GetInstance()->Put(ItemToString(FILE_EDITOR_DIRECTORY), viciHome);
	VEnvironment::GetInstance()->Put(ItemToString(FILE_EDITOR_RESOURCE_DIRECTORY), viciHome + "Resources/");
	VEnvironment::GetInstance()->Put(ItemToString(FILE_ASSET_DIRECTORY), VFilePath(PROJECT_LOCATION) + "Assets/");
	VEnvironment::GetInstance()->Put(ItemToString(FILE_SETTINGS_DIRECTORY), VFilePath(PROJECT_LOCATION) + "Settings/");

	// RELEASE path builds
#else
	VEnvironment::GetInstance()->Put(ItemToString(FILE_EDITOR_RESOURCE_DIRECTORY), runningDirectory + "Assets/Resources/");
	VEnvironment::GetInstance()->Put(ItemToString(FILE_EDITOR_DIRECTORY), runningDirectory);
	VEnvironment::GetInstance()->Put(ItemToString(FILE_ASSET_DIRECTORY), runningDirectory + "Assets/");
	VEnvironment::GetInstance()->Put(ItemToString(FILE_SETTINGS_DIRECTORY), runningDirectory + "Settings/");
#endif

	VEditor editor;
	
	if (editor.Init(argc, argv))
	{
		return editor.Run();
	}
	else
		return -1;
}