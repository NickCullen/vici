#include "Vici.h"
#include "GameObject.h"
#include "Platform.h"
#include <string>
#include "Project.h"

Vici::Vici() : Singleton<Vici>()
{
	_started = false;

}
Vici::~Vici()
{

	//if started is strill true then that means we havnt had time to clean up so do it!
	if (_started)
	{
		OnExit();
		_started = false;
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
	_started = false;
}

void Vici::OnEnteredBackground()
{
	
}

void Vici::OnEnteredFocus()
{
	
}

/*Testing funcs*/
void Vici::AddGameObject(GameObject* go)
{
	
}

void Vici::RemoveGameObject(GameObject* go)
{
	
}
