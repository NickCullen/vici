#include "Vici.h"
#include "GameObject.h"
#include "Platform.h"
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
	if (_instance == NULL)
	{
		_started = false;
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

	//print cwd
	Platform_LogString("Running Directory = %s\n", _cwd);
	
	//initialize stuff
	Display::Init(_cwd);
    _SceneLoader->Init();
	_Layers->Init(_cwd);
	ShaderAsset::LoadSharedCode(_cwd);

	/* Register Asset Types */
	_asset_loader.RegisterAssets();

	/*register components*/
	RegisterComponents();
}

//starts the game
void Vici::Begin()
{
	if (!_started)
	{
		//load first scene (for some reason it wont let me put 0 here without casting it to unsigned in...)
		_SceneLoader->LoadScene((unsigned int)0);

		//dispatch start to all objects
		TTREE_foreach(GameObject*, object, _objects)
		{
			if (object->GetEnabled())
			{
				object->OnStart();
			}
		}

		//dispatch on enabled messages to those who just become enabled
		TTREE_foreach(GameObject*, object, _objects)
		{
			if (object->GetEnabled())
			{
				object->Dispatch(eOnEnable);
			}
		}

		_started = true;
	}
}

/* Update and render funcs */
void Vici::Update()
{
	//lock list
	_objects.Lock();

	TTREE_foreach(GameObject*, object, _objects)
	{
		//only perform update if object hasnt been deleted
		if(!object->IsGarbage() && object->GetEnabled())
			object->Dispatch(eUpdate);
	}

	//unlock
	_objects.Unlock();
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
	//remove from list
	_objects.Remove(go);
}
/*Component registrations*/
void Vici::RegisterComponents()
{
	VCamera::reg = DerivedRegister<VCamera>("VCamera");
	MeshRenderer::reg = DerivedRegister<MeshRenderer>("MeshRenderer");
	Material::reg = DerivedRegister<Material>("Material");
	Light::reg = DerivedRegister<Light>("Light");
}