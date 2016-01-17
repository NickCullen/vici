#include "IComponent.h"
#include "GameObject.h"

IComponent::IComponent()
{
	_go = NULL;
}
IComponent::~IComponent()
{
	
}

void IComponent::OnDestroy()
{
	//remove from game objects component list
	//_go->RemoveComponent(this);
}

void IComponent::OnStart()
{

}

void IComponent::RegisterCallback(EComponentCallback cb, Delegate callback)
{
	//_go->RegisterCallback(cb, callback);
}

SharedReference<GameObject> IComponent::GetGameObject()
{
	return _go;
}
void IComponent::SetGameObject(GameObject& go)
{
	_go = SharedReference<GameObject>(&go);
}