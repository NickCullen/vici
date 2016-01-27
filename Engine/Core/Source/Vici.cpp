#include "Vici.h"
#include "Project.h"

Vici::Vici() : Singleton<Vici>()
{
	bStarted = false;

}
Vici::~Vici()
{

	//if started is strill true then that means we havnt had time to clean up so do it!
	if (bStarted)
	{
		OnExit();
		bStarted = false;
	}
}

//called once when program begins
void Vici::Init()
{
	//print cwd
	_Platform->LogString("Running Directory = %s\n", _Platform->GetCwd());

	//Register Project specific assets
	_Project->RegisterAssetImporters();

	//Register project specific components
	_Project->RegisterComponents();
}

//starts the game
void Vici::Begin()
{
	
}

/* Update and render funcs */
void Vici::Update()
{
	
}


void Vici::Render()
{

}

void Vici::OnExit()
{
	//set back to false
	bStarted = false;
}

void Vici::OnEnteredBackground()
{
	
}

void Vici::OnEnteredFocus()
{
	
}


GameObjectPtr Vici::CreateGameObject()
{
	GameObjectPtr ptr = std::make_shared<GameObject>();
	GameObjects.push_back(ptr);
	return ptr;
}

bool Vici::ReleaseGameObject(GameObjectPtr gameObject)
{
	//NEEDS IMPROVING!
	for (GameObjectList::iterator itr = GameObjects.begin(); itr != GameObjects.end(); itr++)
	{
		if ((*itr) == gameObject)
		{
			GameObjects.erase(itr);
			return true;
		}
	}
	return false;
}

bool Vici::SerializeState(const char* fname)
{
	try
	{
		CreateOutputArchive(outputArch, outputStream, fname);

		_SERIALIZE_VAR(GameObjects, outputArch);

		return true;
	}
	catch ( int e )
	{
		return false;
	}

}