#include "VHash.h"

VHash::VHash()
{
	_hash = 0;
}

VHash::~VHash()
{
}

VHash::VHash(const VHash& other)
{
	_hash = other._hash;
}
VHash::VHash(const char* str)
{
	_hash = Hashify(str);
}
VHash::VHash(char* str)
{
	_hash = Hashify((const char*)str);
}

//references
bool VHash::operator==(vhash_int other)
{
	return(_hash == other);
}
bool VHash::operator==(const VHash& other)
{
	return(_hash == other._hash);
}
bool VHash::operator==(const char* other)
{
	return(_hash == Hashify(other));
}
bool VHash::operator==(char* other)
{
	return(_hash == Hashify((const char*)other));
}

bool VHash::operator!=(vhash_int other)
{
	return(_hash != other);
}
bool VHash::operator!=(const VHash& other)
{
	return(_hash != other._hash);
}
bool VHash::operator!=(const char* other)
{
	return (_hash != Hashify(other));
}
bool VHash::operator!=(char* other)
{
	return (_hash != Hashify((const char*)other));
}

VHash VHash::operator=(vhash_int eq)
{
	_hash = eq;
	return *this;
}
VHash VHash::operator=(const char* eq)
{
	_hash = Hashify(eq);
	return *this;
}

VHash VHash::operator=(char* eq)
{
	_hash = Hashify((const char*)eq);
	return *this;
}

