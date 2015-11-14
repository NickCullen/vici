#include <stdio.h>
#include "Vici.h"
#include "Platform.h"
#include "ViciProject.h"
#include "Display.h"

#include "AssetRegistrar.h"
#include "ComponentRegistrar.h"

#include "ComponentFactory.h"
#include "MeshRenderer.h"

int main(int argc, char** argv)
{
	Vici* v = new Vici();
	ViciProject* proj = new ViciProject();
	
	//Register assets and components
	RegisterAssets();
	RegisterComponents();

	// Default values
	char* runningDirectory = argv[0];
	bool trimEnd = true;

	// Parse args
	if (argc > 1)
	{
		for(int i = 1; i < argc; i+=2)
		{
			char* param = argv[i];
			char* value = argv[i+1];
			
			// Running Directory param
			if(strcmp(param, "-rd") == 0)
			{
				runningDirectory = value;
				trimEnd = false;
			}
		}
	}
	
	// Set current working directory
	_Platform->SetCwd(runningDirectory, trimEnd);
	
	// Setup Display
	Display* display = new Display();
	display->Init(_Platform->GetCwd());
	
	v->Init();

	v->Begin();

	_Platform->EnterLoop(v);

	delete(display);
	delete(proj);
	delete(v);
	
	return 0;
}

