#include "VString.h"
#include <string.h>

using namespace Core;

const uint32 VString::INVALID_POS(-1);

VString::VString()
{
   /* Length = 0;
    Capacity = 10;

    Data = new char[Capacity];
    Data[0] = '\0';

    CalculateHash();*/
}

VString::VString(const char* str)
{
    Length = strlen(str);
    Capacity = Length + 1;
    Data = new char[Capacity];
    strncpy(Data, str, Length);
	Data[Length] = '\0';

    CalculateHash();
}

VString::VString(const VString& other)
{
    Length = other.GetLength();
    Capacity = Length + 1;
    Data = new char[Capacity];
    strncpy(Data, other.Data, Length);
	Data[Length] = '\0';

    CalculateHash();
}

VString::~VString()
{
    Free();
}

void VString::Free()
{
    if(Data != nullptr)
    {
        delete [] Data;
    }
}

void VString::CalculateHash()
{
    Hash = 2166136261;
    
    for(uint32 i = 0; i < Length; i++)
    {
        Hash ^= Data[i];
        Hash *= 16777619;
    }
}

bool VString::operator==(const VString& other) const
{
    return (Hash == other.Hash);
}

bool VString::operator!=(const VString& other) const
{
    return (Hash != other.Hash);
}

VString VString::operator+(const VString& other) const
{
	VString Ret;

	Ret.Length = Length + other.Length;
	Ret.Capacity = Ret.Length + 1;


	Ret.Data = new char[Ret.Capacity];

	if (Length > 0)
	{
		strncpy(Ret.Data, Data, Length);
	}

	if (other.Length > 0)
	{
		char* offset = Ret.Data + Length;
		strncpy(offset, other.Data, other.Length);
	}

	Ret.Data[Ret.Length] = '\0';

	Ret.CalculateHash();

	return Ret;
}

VString VString::operator+(const char* other) const
{
	VString Ret;

	uint32 OtherLen = strlen(other);

	Ret.Length = Length + OtherLen;
	Ret.Capacity = Ret.Length + 1;


	Ret.Data = new char[Ret.Capacity];

	if (Length > 0)
	{
		strncpy(Ret.Data, Data, Length);
	}

	if (OtherLen > 0)
	{
		char* offset = Ret.Data + Length;
		strncpy(offset, other, OtherLen);
	}

	Ret.Data[Ret.Length] = '\0';

	Ret.CalculateHash();

	return Ret;
}

uint32 VString::FirstIndexOf(const VString& other) const
{
	return FirstIndexOf(other.Data);
}

uint32 VString::FirstIndexOf(const char* other) const
{
	uint32 OtherLen = strlen(other);

	for (uint32 i = 0; i < Length; i++)
	{
		uint32 StartPos = i;

		for (uint32 j = 0; j < OtherLen; j++)
		{
			if (Data[i] != other[j])
				break;

			// Out of range of this string, therefore it must not exist
			if (++i >= Length)
				return INVALID_POS;

			// matches all search term
			if (((j + 1) == OtherLen))
				return StartPos;
		}
	}

	return INVALID_POS;
}

uint32 VString::LastIndexOf(const VString& other) const
{
	return LastIndexOf(other.Data);
}

uint32 VString::LastIndexOf(const char* other) const
{
	uint32 OtherLen = strlen(other);

	for (int32 i = Length - 1; i >= 0; i--)
	{
		uint32 StartPos = i;

		for (int32 j = OtherLen - 1; j >= 0; j--)
		{
			if (Data[i] != other[j])
				break;

			// Out of range of this string, therefore it must not exist
			if (--i < 0)
				return INVALID_POS;

			// matches all search term
			if (j == 0)
				return StartPos - OtherLen + 1;
		}
	}

	return INVALID_POS;
}

VString VString::GetSubstr(uint32 Start, uint32 Num) const
{
	VString Ret;
	Ret.Capacity = Num + 1;
	Ret.Data = new char[Ret.Capacity];

	uint32 Count = 0;
	for (uint32 i = Start; i < Length && Count < Num; i++, Count++)
	{
		Ret.Data[Count] = Data[i];
	}
	Ret.Data[Count] = '\0';
	Ret.Length = Count;

	Ret.CalculateHash();

	return Ret;
}