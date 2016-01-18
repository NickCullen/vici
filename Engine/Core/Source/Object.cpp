#include "Object.h"

//static init
uint32 Object::Count = 0;

Object::Object()
{
	bIndestructable = false;
	InstanceID = ++Count;
	bGarbage = false;
}

Object::~Object()
{

}

//copy ctor
Object::Object(const Object& other)
{
	InstanceID = other.InstanceID;
	MyHash = other.MyHash;
}

bool Object::operator==(Object& o)
{
	return (InstanceID == o.InstanceID && MyHash == o.MyHash);
}

bool Object::operator!=(Object& o)
{
	return (InstanceID != o.InstanceID && MyHash != o.MyHash);
}


void Object::MakeIndestructable()
{
	bIndestructable = true;
}


void Object::Destroy(Object* o)
{
	//if it isnt destructable
	if (!o->bIndestructable)
	{
		//destroy it so it has a chance to clean up (and remove itself from lists)
		o->OnDestroy();

		//if it is garbage it means 
		//something else if going to delete this (e.g a locked gameobject list)
		if(!o->IsGarbage()) 
			delete(o);
	}
}