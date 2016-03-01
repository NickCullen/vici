#include "VString.h"
#include <string>

// def
struct VStringImpl
{
	std::string Data;
};

VString::VString()
{
	Impl = new VStringImpl();
}

VString::VString(const VString& other)
{
	Impl = new VStringImpl();
	*Impl = *other.Impl;
}

VString::VString(const char* str)
{
	Impl = new VStringImpl();
	Impl->Data = str;
}

VString::~VString()
{
	delete(Impl);
}

VString::operator const char*()
{
	return Impl->Data.c_str();
}