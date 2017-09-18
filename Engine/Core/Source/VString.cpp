#include "VString.h"
#include <string>

using namespace Core;

VString::VString()
{
    Length = 0;
    Capacity = 10;

    Data = new char[Capacity];
    Data[0] = '\0';

    CalculateHash();
}

VString::VString(const char* str)
{
    Length = strlen(str);
    Capacity = Length + 1;
    Data = new char[Capacity];
    strncpy(Data, str, Length);

    CalculateHash();
}

VString::VString(const VString& other)
{
    Length = other.GetLength();
    Capacity = Length + 1;
    Data = new char[Capacity];
    strncpy(Data, other.Data, Length);

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