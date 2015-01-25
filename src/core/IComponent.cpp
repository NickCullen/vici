#include "IComponent.h"

IComponent::IComponent()
{
	_go = NULL;
}
IComponent::~IComponent()
{
	
}

void IComponent::Init(GameObject* go, rapidxml::xml_node<char>* data)
{
	/*initial vars*/
	_go = go;

}

void IComponent::OnDestroy()
{
	//remove from game objects component list
	_go->RemoveComponent(this);
}

void IComponent::RegisterCallback(EComponentCallback cb, Delegate callback)
{
	_go->RegisterCallback(cb, callback);
}