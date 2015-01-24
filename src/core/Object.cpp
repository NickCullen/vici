#include "Object.h"

//static init
unsigned int Object::_count = 0;

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
}

bool Object::operator==(Object& o)
{
	return (_instance == o._instance);
}

bool Object::operator!=(Object& o)
{
	return (_instance != o._instance);
}


void Object::MakeIndestructable()
{
	_indestructable = true;
}