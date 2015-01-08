#include "IComponent.h"

IComponent::IComponent()
{

}
IComponent::~IComponent()
{
	
}

/*Helper Functions*/
GameObject* IComponent::GetGameObject()
{
	return _go;
}

void IComponent::Init(GameObject* go, rapidxml::xml_node<char>* data)
{
	_go = go;

}

void IComponent::RegisterCallback(EComponentCallback callback)
{
	_go->RegisterCallback(this, callback);
}