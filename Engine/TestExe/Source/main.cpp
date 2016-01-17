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

void Tests()
{
	std::string data = "/TestSerialization.json";
	_Platform->GetFullPath(data);

	CreateOutputArchive(outputArch, outputStream, data);

	GameObject go;

	Transform* t = go.GetTransform();

	t->Translate(100, 0, 100);
	t->Scale(20, 30, 40);
	t->Rotate(90, 0, 1, 0);

	TestComponent* comp = go.AddComponent<TestComponent>("TestComponent");

	_SERIALIZE_VAR_NAME(go, "MyObject", outputArch);

}

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
	
	// Deserialize the data
	std::string displayData = "/Settings/Display.json";
	_Platform->GetFullPath(displayData);
 
	// Load the data into memory
	CreateInputArchive(arch, inputStream, displayData);
    
	// Deserialize
	_SERIALIZE_VAR_NAME(*display, "Display", arch);


	Tests();

	// Initialize Display
	display->Init();
    
	v->Init();

	v->Begin();

	_Platform->EnterLoop(v);

//	delete(display);
	delete(proj);
	delete(v);
	
	return 0;
}

