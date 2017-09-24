#pragma once

#include "CoreTypes.h"

namespace Core
{
    template<typename T>
    class TArray
    {
    private:
        uint32 Length = 0;
    
        uint32 Capacity = 0;
    
        T* Data = nullptr;
    
    public:
        TArray()
        {
            Reserve(10); // Start with 10 elements reserve
        }
        
        TArray(uint32 ReserveSize)
        {
            Reserve(ReserveSize);
        }
        
        TArray(const TArray<T>& other)
        {
            Reserve(other.Capacity);
            CopyToData(other.Data, Capacity);
        }
    
        inline uint32 GetLength() const { return Length; }
        inline uint32 GetCapacity() const { return Capacity; }
        inline T* GetData() const { return Data; }
    private:
        void Reserve(uint32 NewSize)
        {
            if(Data != nullptr)
            {
                T* OldData = Data;
                Data = new T[NewSize];

                Capacity = NewSize;

                delete [] OldData;      // Delete old Data
            }
            else
            {
                Data = new T[NewSize];
                Capacity = NewSize;
            }
        }

        void Resize(uint32 NewSize)
        {
            if(Data != nullptr)
            {
                T* OldData = Data;
                Data = new T[NewSize];
                
                CopyToData(OldData, Capacity); // Ensure old data is copied over
                Capacity = NewSize;

                delete [] OldData;      // Delete old Data
            }
            else
            {
                Data = new T[NewSize];
                Capacity = NewSize;
            }
        }

        void CopyToData(T* NewData, uint32 NewDataSize)
        {
            for(uint32 i; i < NewDataSize; i++)
                Data[i] = NewData[i];
        }
    };
}
