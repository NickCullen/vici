#include "IDrawable.h"

IDrawable::IDrawable()
{

}
IDrawable::~IDrawable()
{

}

void IDrawable::Init(XmlNode& data)
{
	//important to call IComponent init
	IComponent::Init(data);

	//add to game objects render list
	_go->RenderList()->PushBack(this);
}

void IDrawable::OnDestroy()
{
	//call IComponent OnDestroy
	IComponent::OnDestroy();

	//remove from components render list
	_go->RenderList()->Remove(this);

}