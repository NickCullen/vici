#pragma once

struct VStringImpl;

#include "CoreAPI.h"

class CORE_API VString
{
private:
	VStringImpl* Impl;	// Pimpl idiom for std::string impl

public:
	VString();
	VString(const VString& other);
	VString(const char* str);

	~VString();

	// Cast operator
	operator const char*();
};