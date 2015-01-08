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

	
}