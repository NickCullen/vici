#pragma once

#include "CoreAPI.h"
#include "VTypes.h"
#include <memory>

template<typename T>
class CORE_API VDynamicPool
{
	class VPoolPointer
	{
		friend class VDynamicPool;
	private:
		uint32 Index;		// Index into Pool array
		VDynamicPool* Pool;	// Pointer to the pool so we can retrieve the object

		// Only pool object allowed to create these
		VPoolPointer() = default;
		
	public:
		~VPoolPointer() = default;

		T* operator->()
		{
			return Pool->GetPtr(Index);
		}
	};

	friend class VPoolPointer;
private:
	T* Data;	// Array of data

	uint32 MaxCount;	// Total number of allocated objects

	T* Begin;		// Pointer to the start of the pool

	T* End;			// Pointer to the end of the pool

	// Only callable by VPoolPointers
	inline T* GetPtr(uint32 index)
	{
		return &Data[index];
	}

public:
	VDynamicPool()
		: Data(nullptr),
		Begin(nullptr),
		End(nullptr),
		MaxCount(0)
	{
	}

	VDynamicPool(uint32 count)
		: Data(nullptr),
		Begin(nullptr),
		End(nullptr),
		MaxCount(0)
	{
		Resize(count);
	}

	~VDynamicPool()
	{
		delete [] Data;
	}

	// Resizes array to the newCount * sizeof(T)
	void Resize(uint32 newCount)
	{
		uint32 newSize = newCount * sizeof(T);
		// Data already exists
		if (Data != nullptr)
			Data = (T*)realloc(Data, newSize);
		else
			Data = (T*)malloc(newSize);

		MaxCount = newCount;
		Begin = &Data[0];
		End = &Data[MaxCount];
	}

	VPoolPointer Get(uint32 index)
	{
		if (index >= MaxCount)
			Resize(index + (index >> 1));

		VPoolPointer ptr;
		ptr.Index = index;
		ptr.Pool = this;

		return ptr;
	}
};