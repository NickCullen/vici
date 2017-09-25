#pragma once

#include "CoreAPI.h"
#include "CoreTypes.h"

namespace Core
{
    class CORE_API VString
    {
	public:
		static const uint32 INVALID_POS;

    private:
        char* Data = nullptr;
    
        uint32 Length = 0;
        uint32 Capacity = 0;
    
        uint32 Hash = 0;
    public:
        VString();
        VString(const char* str);
        VString(const VString& other);
    
        ~VString();

        VString& operator=(const VString& other);
        VString& operator=(const char* other);

        bool operator==(const VString& other) const;
        bool operator!=(const VString& other) const;
        
		VString operator+(const VString& other) const;
		VString operator+(const char* other) const;

		uint32 FirstIndexOf(const VString& other) const;
		uint32 FirstIndexOf(const char* other) const;

		uint32 LastIndexOf(const VString& other) const;
		uint32 LastIndexOf(const char* other) const;

		VString GetSubstr(uint32 Start, uint32 Num) const;

        uint32 operator%(uint32 Num) const;

        inline uint32 GetLength() const
        {
            return Length;
        }
    
        inline uint32 GetCapacity() const
        {
            return Capacity;
        }
    
        inline const char* GetData() const
        {
            return (const char*)Data;
        }

        inline uint32 GetHash() const
        {
            return Hash;
        }

    private:
        void CalculateHash();

        void Free();
    };
}
