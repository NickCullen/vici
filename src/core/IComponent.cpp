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

void IComponent::RegisterCallback(EComponentCallback callback)
{
	_go->RegisterCallback(this, callback);
}