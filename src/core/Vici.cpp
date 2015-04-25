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

Vici::Vici() : Singleton<Vici>(this)
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
	
	//initialize stuff
	_Display->Init(_Platform->GetCwd());
    _SceneLoader->Init();
	_Layers->Init(_Platform->GetCwd());
	_Squirrel->Init();

	//call some required static methods on classes
	ShaderAsset::LoadSharedCode(_Platform->GetCwd());

	//Register Vici Asset Types
	_asset_loader.RegisterAssets();

	//register Vici components
	RegisterComponents();

	//Register Project specific assets
	_Project->RegisterAssetImporters();

	//Register project specific components
	_Project->RegisterComponents();
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
	else
	{
		_Platform->LogString("Cannot begin engine as _started is already set to true\n");
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

void Vici::OnExit()
{
	//delete all objects left on tree
	_objects.Lock();

	TTREE_foreach(GameObject*, obj, _objects)
	{
		Object::Destroy(obj);
	}

	_objects.Unlock();

	//unload assets
	_Assets->UnloadAll();

	//cleanup components
	ComponentFactory::CleanUp();
	AssetFactory::CleanUp();
	ShaderAsset::UnloadSharedCode();

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
	_objects.Insert(go);
}

void Vici::RemoveGameObject(GameObject* go)
{
	//remove from list
	_objects.Remove(go);
}

/* Component registrations */
void Vici::RegisterComponents()
{
	VCamera::reg = ComponentRegister<VCamera>("VCamera");
	MeshRenderer::reg = ComponentRegister<MeshRenderer>("MeshRenderer");
	Material::reg = ComponentRegister<Material>("Material");
	Light::reg = ComponentRegister<Light>("Light");
	ScriptableComponent::reg = ComponentRegister<ScriptableComponent>("ScriptableComponent");
}