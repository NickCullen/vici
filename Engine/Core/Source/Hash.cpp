#include "Hash.h"

Hash::Hash()
{
	_hash = 0;
}

Hash::~Hash()
{
}

Hash::Hash(const Hash& other)
{
	_hash = other._hash;
}
Hash::Hash(const char* str)
{
	_hash = Hashify(str);
}
Hash::Hash(char* str)
{
	_hash = Hashify((const char*)str);
}

//references
bool Hash::operator==(hash_int other)
{
	return(_hash == other);
}

bool Hash::operator==(const char* other)
{
	return(_hash == Hashify(other));
}
bool Hash::operator==(char* other)
{
	return(_hash == Hashify((const char*)other));
}

bool Hash::operator!=(hash_int other)
{
	return(_hash != other);
}

bool Hash::operator!=(const char* other)
{
	return (_hash != Hashify(other));
}
bool Hash::operator!=(char* other)
{
	return (_hash != Hashify((const char*)other));
}

Hash Hash::operator=(hash_int eq)
{
	_hash = eq;
	return *this;
}
Hash Hash::operator=(const char* eq)
{
	_hash = Hashify(eq);
	return *this;
}

Hash Hash::operator=(char* eq)
{
	_hash = Hashify((const char*)eq);
	return *this;
}

bool Hash::operator<(hash_int other)
{
	return(_hash < other);
}

bool Hash::operator<(const char* other)
{
	return (_hash < Hashify(other));
}
bool Hash::operator<(char* other)
{
	return (_hash < Hashify((const char*)other));
}

bool Hash::operator>(hash_int other)
{
	return(_hash > other);
}

bool Hash::operator>(const char* other)
{
	return (_hash > Hashify(other));
}
bool Hash::operator>(char* other)
{
	return (_hash > Hashify((const char*)other));
}