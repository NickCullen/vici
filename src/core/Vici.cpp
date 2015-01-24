#include "Vici.h"
#include "GameObject.h"
#include "Platform.h"
#include "rapidxml/rapidxml.hpp"
#include <string>
#include "Display.h"
#include "SceneLoader.h"
#include "Camera.h"
#include "LayerSystem.h"
#include "Components.h"
#include "ComponentFactory.h"

/*Static decl*/
Vici* Vici::_instance = NULL;

//function for inserting game objects
int CompareGameObject(GameObject* lhs, GameObject* rhs)
{
	if (lhs->ID() < rhs->ID()) return -1;
	else if (lhs->ID() > rhs->ID()) return 0;
	else return 1;
}

Vici::Vici()
{
	if (_instance == NULL)
	{
		_started = false;
		_instance = this;

		//set tree comparison func
		_objects.SetComparisonFunc(CompareGameObject);
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
		
		TTREE_foreach(GameObject*, object, _objects)
		{
			object->Dispatch(eAwake);
		}

		TTREE_foreach(GameObject*, object, _objects)
		{
			if (object->GetEnabled())
			{
				object->Dispatch(eOnEnable);
			}
		}

		TTREE_foreach(GameObject*, object, _objects)
		{
			object->Dispatch(eStart);
		}

		_started = true;
	}
}

/* Update and render funcs */
void Vici::Update()
{
	TTREE_foreach(GameObject*, object, _objects)
	{
		object->Dispatch(eUpdate);
	}
}

void Vici::Render()
{
	TLIST_foreach(VCamera*, camera, _cameras)
	{
		//prepare the scene
		camera->PrepareScene();

		//now do renderings
		camera->Render();
	}
}

char* Vici::GetCwd()
{
	return _cwd;
}

/*Testing funcs*/
void Vici::AddGameObject(GameObject* go)
{
	_objects.Insert(go);
}

void Vici::RemoveGameObject(GameObject* go)
{
	//TODO
}
/*Component registrations*/
void Vici::RegisterComponents()
{
	VCamera::reg = DerivedRegister<VCamera>("VCamera");
	MeshRenderer::reg = DerivedRegister<MeshRenderer>("MeshRenderer");
}