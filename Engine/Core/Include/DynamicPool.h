#pragma once

#include "CoreAPI.h"
#include "VTypes.h"
#include <memory>

template<typename T>
class CORE_API VDynamicPool
{
private:
	T* Data;	// Array of data

	uint32 MaxSize;	// Total allocated space of the pool

	T* Begin;		// Pointer to the start of the pool

	T* End;			// Pointer to the end of the pool

public:
	VDynamicPool()
		: Data(nullptr),
		Begin(nullptr),
		End(nullptr),
		MaxSize(0)
	{
	}

	VDynamicPool(uint32 count)
		: Data(nullptr),
		Begin(nullptr),
		End(nullptr),
		MaxSize(0)
	{
		Resize(count * sizeof(T));
	}

	~VDynamicPool()
	{
		delete [] Data;
	}

	// Resizes array to the newSize in bytes
	void Resize(uint32 newSize)
	{
		// Data already exists
		if (Data != nullptr)
			Data = (T*)realloc(Data, newSize);
		else
			Data = (T*)malloc(newSize);

		MaxSize = newSize;
		Begin = &Data[0];
		End = &Data[MaxSize];
	}

	T* Get(uint32 index)
	{
		uint32 offset = sizeof(T) * index;
		if (offset >= MaxSize)
			Resize(offset + (offset >> 1));

		return &Data[index];
	}
};