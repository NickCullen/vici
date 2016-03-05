#include "Editor.h"
#include "EngineMacros.h"
#include "Environment.h"
#include "FilePath.h"

int main(int argc, const char** argv)
{
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