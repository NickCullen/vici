#pragma once

struct VStringImpl;

#include "CoreAPI.h"

class CORE_API VString
{
protected:
	VStringImpl* Impl;	// Pimpl idiom for std::string impl

public:
	VString();
	VString(const VString& other);
	VString(const char* str);

	~VString();

	// Access
	const char* c_str();

	// Set
	void SetString(const VString& str);

	// operator overloads
	operator const char*();
	operator char*() const;
	VString operator+(const VString& other);
	VString operator+(const char* other);
	VString& operator=(const VString& other);
	VString& operator=(const char* other);
};