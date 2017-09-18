#pragma once

#include "CoreAPI.h"
#include "CoreTypes.h"

namespace Core
{
    class CORE_API VString
    {
    private:
        char* Data = nullptr;
    
        uint32 Length = 0;
        uint32 Capacity = 0;
    
        uint64 Hash = 0;
    public:
        VString();
        VString(const char* str);
        VString(const VString& other);
    
        ~VString();

        void Free();

        bool operator==(const VString& other) const;
        bool operator!=(const VString& other) const;
        
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

    private:
        void CalculateHash();
    };
}
