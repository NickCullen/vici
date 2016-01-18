#include "Hash.h"

Hash::Hash()
{
	Value = 0;
}

Hash::~Hash()
{
}

Hash::Hash(const Hash& other)
{
	Value = other.Value;

#ifdef VICI_DEBUG
	Friendly = other.Friendly;
#endif
}
Hash::Hash(const char* str)
{
	Value = Hashify(str);

#ifdef VICI_DEBUG
	Friendly = str;
#endif
}
Hash::Hash(char* str)
{
	Value = Hashify((const char*)str);

#ifdef VICI_DEBUG
	Friendly = str;
#endif
}

//references
bool Hash::operator==(hash_int other)
{
	return(Value == other);
}

bool Hash::operator==(const char* other)
{
	return(Value == Hashify(other));
}
bool Hash::operator==(char* other)
{
	return(Value == Hashify((const char*)other));
}

bool Hash::operator!=(hash_int other)
{
	return(Value != other);
}

bool Hash::operator!=(const char* other)
{
	return (Value != Hashify(other));
}
bool Hash::operator!=(char* other)
{
	return (Value != Hashify((const char*)other));
}

Hash Hash::operator=(hash_int eq)
{
	Value = eq;
	return *this;
}
Hash Hash::operator=(const char* eq)
{
	Value = Hashify(eq);
	return *this;
}

Hash Hash::operator=(char* eq)
{
	Value = Hashify((const char*)eq);
	return *this;
}

bool Hash::operator<(hash_int other)
{
	return(Value < other);
}

bool Hash::operator<(const char* other)
{
	return (Value < Hashify(other));
}
bool Hash::operator<(char* other)
{
	return (Value < Hashify((const char*)other));
}

bool Hash::operator>(hash_int other)
{
	return(Value > other);
}

bool Hash::operator>(const char* other)
{
	return (Value > Hashify(other));
}
bool Hash::operator>(char* other)
{
	return (Value > Hashify((const char*)other));
}