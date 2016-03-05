#include "VString.h"
#include <string>

#define ENSURE_IMPL if(Impl == nullptr || (unsigned int)Impl == 0xcccccccc) Impl = new VStringImpl();

// def
struct VStringImpl
{
	std::string Data;

	VStringImpl() = default;
	VStringImpl(const std::string& other) { Data = other; }
};

VString::VString()
	:Impl(nullptr)
{
	ENSURE_IMPL
}

VString::VString(const VString& other)
{
	ENSURE_IMPL
	*Impl = *other.Impl;
}

VString::VString(const char* str)
{
	ENSURE_IMPL
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

VString::operator char*() const
{
	return (char*)Impl->Data.c_str();
}

VString VString::operator+(const VString& other)
{
	ENSURE_IMPL
	std::string newString = Impl->Data + other.Impl->Data;
	return VString(newString.c_str());
}

VString VString::operator+(const char* other)
{
	ENSURE_IMPL
	std::string newString = Impl->Data + other;
	return VString(newString.c_str());
}

VString& VString::operator=(const VString& other)
{
	ENSURE_IMPL
	Impl->Data = other.Impl->Data;
	return *this;
}

VString& VString::operator=(const char* other)
{
	ENSURE_IMPL
	Impl->Data = other;
	return *this;
}