#include "IDrawable.h"

IDrawable::IDrawable()
{

}
IDrawable::~IDrawable()
{

}


void IDrawable::OnDestroy()
{
	//call IComponent OnDestroy
	IComponent::OnDestroy();

	//remove from components render list
	//_go->RenderList()->Remove(this);

}