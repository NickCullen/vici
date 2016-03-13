#pragma once

#include "Array.h"

class CORE_API VString
{
protected:
	VArray<char> Data;	// The pool of data for our characters

	uint32 Length;
public:
	VString();
	VString(const char* str);
	VString(const VArray<char>& pool);

	~VString();

	// Access
	const char* GetCString() const;
	char& operator[](int32 index);
	const char& operator[](int32 index) const;

	// Set
	void SetString(const VString& str);

	// operator overloads
	operator const char*() const;
	operator char*() const;

	VString operator+(const VString& other) const;
	VString operator+(const char* other)  const;

	// Getters
	inline uint32 GetLength() const { return Length; }

	// Setters
	inline void SetLength(uint32 len) { Length = len; }
};