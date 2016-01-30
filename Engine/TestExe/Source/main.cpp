#include <stdio.h>
#include "Vici.h"
#include "Platform.h"
#include "ViciProject.h"
#include "Display.h"

#include "AssetRegistrar.h"
#include "ComponentRegistrar.h"

#include "ComponentFactory.h"

#include "Serialization.h"

#include "TextFile.h"

#include "GameObject.h"
#include "TestComponent.h"
#include "VTime.h"

void Tests()
{
	std::string data = "/TestSerialization.json";
	_Platform->GetFullPath(data);

	/*GameObject goDesr;

	CreateInputArchive(inputArch, inputStream, data);

	inputArch(goDesr);
	return;*/

	GameObjectPtr go = _Vici->CreateGameObject();

	TestComponent* tc = go->AddComponent<TestComponent>("TestComponent");
	tc->SetGameObject(go);

	_Vici->SerializeState(data.c_str());

}

int main(int argc, char** argv)
{
	Vici* v = new Vici();
	ViciProject* proj = new ViciProject();
	
	//Register assets and components
	RegisterAssets();
	RegisterComponents();

	// Initialize platform
	if (!_Platform->Init())
		printf("Could not initialize platform\n");

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
	Display* display;
	if (_Platform->DeserializeEngineComponent(kDisplay, "/Settings/Display.xml", (void**)&display))
	{
		display->Init();
	}

	

	// Deserialize the data
	//
 
	// Load the data into memory
	//CreateInputArchive(arch, inputStream, displayData);
    
	// Deserialize
	//_SERIALIZE_VAR_NAME(*display, "Display", arch);


	Tests();

	// Initialize Display
	//display->Init();
    
	v->Init();

	v->Begin();

	
//	delete(display);
	delete(proj);
	delete(v);
	
	return 0;
}

