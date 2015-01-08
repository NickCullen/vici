#include "Vici.h"
#include "GameObject.h"
#include "Platform.h"
#include "rapidxml\rapidxml.hpp"
#include <string>
#include "Display.h"
#include "SceneLoader.h"
#include "Camera.h"
#include "LayerSystem.h"
#include "Components.h"
#include "ComponentFactory.h"

/*Static decl*/
Vici* Vici::_instance = NULL;

Vici::Vici()
{
	_started = false;
	if (_instance == NULL)
	{
		_instance = this;
	}
}
Vici::~Vici()
{
	_started = false;
}


//called once when program begins
void Vici::Init()
{
	//set the cwd
	Platform_Getcwd(_cwd, BUFF_LEN);

	//initialize stuff
	LayerSystem::Init(_cwd);
	Display::Init(_cwd);
	SceneLoader::Init(this);

	/*register components*/
	RegisterComponents();
}

//starts the game
void Vici::Begin()
{
	if (!_started)
	{
		//load first scene (for some reason it wont let me put 0 here without casting it to unsigned in...)
		SceneLoader::LoadScene((unsigned int)0);
		
		for (unsigned int i = 0; i < _objects.size(); i++)
		{
			_objects[i]->Awake();
		}

		for (unsigned int i = 0; i < _objects.size(); i++)
		{
			if (_objects[i]->GetEnabled())
			{
				_objects[i]->OnEnable();
			}
		}

		for (unsigned int i = 0; i < _objects.size(); i++)
		{
			_objects[i]->Start();
		}

		_started = true;
	}
}

/* Update and render funcs */
void Vici::Update()
{
	for (unsigned int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->Update();
	}
}

void Vici::Render()
{
	for (unsigned int i = 0; i < _cameras.size(); i++)
	{
		//prepare the scene
		_cameras[i]->PrepareScene();

		//now do renderings
		_cameras[i]->Render();
	}
}

char* Vici::GetCwd()
{
	return _cwd;
}

/*Testing funcs*/
void Vici::AddGameObject(GameObject* go)
{
	_objects.push_back(go);
}

/*Component registrations*/
void Vici::RegisterComponents()
{
	VCamera::reg = DerivedRegister<VCamera>("VCamera");
	MeshRenderer::reg = DerivedRegister<MeshRenderer>("MeshRenderer");
}