#include "IComponent.h"

IComponent::IComponent()
{
	_go = NULL;
}
IComponent::~IComponent()
{
	
}

void IComponent::Init(rapidxml::xml_node<char>* data)
{

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