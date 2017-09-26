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
        
        void Add(const T& Item)
        {
            // Ensure space
            if((Length+1) >= Capacity)
                Resize(Capacity + (uint32)(Capacity * 1.5f));

            Data[Length++] = Item;
        }

        T& operator[](uint32 Index)
        {
            if(Index < Length)
                return Data[Index];
            
            throw "Index out of range";
        }

        const T& operator[](uint32 Index) const
        {
            if(Index < Length)
                return Data[Index];
        
            throw "Index out of range";
        }

        bool Remove(uint32 Index)
        {
            if(Index < Length)
            {
                // Swap last for this
                Data[Index] = Data[Length-- -1];
                return true;
            }
            return false;
        }

        bool Remove(const T& Item)
        {
            // Find index and use that overloaded fnc.
            for(uint32 i = 0; i < Length; i++)
            {
                if(Data[i] == Item)
                    return Remove(i);
            }   

            return false;
        }

        void Clear()
        {
            Length = 0; // As simple as setting to 0

            // Although, if the list is taking up an absurd
            // ammount of memory, shrink it down
            if(sizeof(T) * Capacity >= 1024)
                Resize(10);
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
            // Ideally should use memcpy... ;)
            for(uint32 i = 0; i < NewDataSize; i++)
                Data[i] = NewData[i];
        }
    };
}
