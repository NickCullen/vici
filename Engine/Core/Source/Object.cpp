#include "Object.h"

//static init
uint32 Object::_count = 0;

Object::Object()
{
	_indestructable = false;
	_instance = ++_count;
	_garbage = false;
}

Object::~Object()
{

}

//copy ctor
Object::Object(const Object& other)
{
	_instance = other._instance;
	_hash = other._hash;
}

bool Object::operator==(Object& o)
{
	return (_instance == o._instance && _hash == o._hash);
}

bool Object::operator!=(Object& o)
{
	return (_instance != o._instance && _hash != o._hash);
}


void Object::MakeIndestructable()
{
	_indestructable = true;
}


void Object::Destroy(Object* o)
{
	//if it isnt destructable
	if (!o->_indestructable)
	{
		//destroy it so it has a chance to clean up (and remove itself from lists)
		o->OnDestroy();

		//if it is garbage it means 
		//something else if going to delete this (e.g a locked gameobject list)
		if(!o->IsGarbage()) 
			delete(o);
	}
}