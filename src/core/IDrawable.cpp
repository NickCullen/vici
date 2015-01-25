#include "IDrawable.h"

IDrawable::IDrawable()
{

}
IDrawable::~IDrawable()
{

}

void IDrawable::Init(GameObject* go, rapidxml::xml_node<char>* data)
{
	//important to call IComponent init
	IComponent::Init(go, data);

	//add to game objects render list
	go->RenderList()->PushBack(this);
}

void IDrawable::OnDestroy()
{
	//call IComponent OnDestroy
	IComponent::OnDestroy();

	//remove from components render list
	_go->RenderList()->Remove(this);

}