#include "VString.h"
#include <string>

VString::VString()
	: Data(10),
	Length(0)
{
	
}

VString::VString(const char* str)
{
	Length = (uint32)strlen(str);
	Data.SetCount(Length+1);
	for (uint32 i = 0; i < Length; i++)
		Data[i] = str[i];
	Data[Length] = '\0';
}

VString::VString(const VArray<char>& arr)
	:Data(arr)
{
	Length = arr.GetAt(arr.GetCount()-1) == '\0' ? arr.GetCount() - 1 : arr.GetCount();
}

VString::~VString()
{
}

const char* VString::GetCString() const
{
	return Data.GetData();
}

void VString::SetString(const VString& str)
{
	Data = str.Data;
	Length = str.Length;
}

VString::operator const char*() const
{
	return Data.GetData();
}

VString::operator char*() const
{
	return (char*)Data.GetData();
}

VString VString::operator+(const VString& other) const
{
	uint32 len = Length + other.Length + 1;

	// Pool to store new data
	VArray<char> newArr(len);

	// Copy this string
	for (uint32 i = 0; i < Length; i++)
		newArr.Add(Data.GetAt(i));

	// Copy next string
	for (uint32 i = 0; i < other.Length; i++)
		newArr.Add(other.Data.GetAt(i));

	// Null terminate
	newArr[len] = '\0';

	return newArr;
}

VString VString::operator+(const char* other) const
{
	uint32 strLen = (uint32)strlen(other);
	uint32 len = Length + strLen;

	// Pool to store new data
	VArray<char> newArr(len);

	// Copy this string
	for (uint32 i = 0; i < Length-1; i++)
		newArr[i] = Data.GetAt(i);

	// Copy next string
	for (uint32 i = 0; i < strLen; i++)
		newArr[Length+i] = other[i];

	// Null terminate
	newArr[len] = '\0';

	return newArr;
}

//VString& VString::operator=(const VString& other)
//{
//	Data = other.Data;
//	Length = other.Length;
//
//	return *this;
//}

VString& VString::operator=(const char* other)
{
	Length = (uint32)strlen(other) + 1;
	Data.SetCount(Length);

	for (uint32 i = 0; i < Length; i++)
		Data[i] = other[i];

	return *this;
}


uint32 VString::GetLength() const
{
	return Length;
}