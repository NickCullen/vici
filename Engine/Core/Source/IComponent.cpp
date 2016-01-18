#include "IComponent.h"
#include "GameObject.h"

IComponent::IComponent()
{
	MyGameObject = NULL;
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

GameObject* IComponent::GetGameObject()
{
	return MyGameObject;
}
void IComponent::SetGameObject(GameObject* go)
{
	MyGameObject = go;
}