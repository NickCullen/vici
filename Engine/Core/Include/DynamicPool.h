#pragma once

#include "CoreAPI.h"
#include "VTypes.h"
#include <memory>

/**
 * Pool of objects that can resize if
 * a call to Get exceeds MaxCount
 */
template<typename T>
class CORE_API VDynamicPool
{
	/**
	 * Use for safe access when working with dynamic pools
	 */
	class VPoolPointer
	{
		friend class VDynamicPool;
	private:
		uint32 Index;		// Index into Pool array
		VDynamicPool* Pool;	// Pointer to the pool so we can retrieve the object

		// Only pool object allowed to create these
		VPoolPointer(uint32 index, VDynamicPool* pool)
			:Index(index),
			Pool(pool)
		{}
		
	public:
		~VPoolPointer() = default;

		int GetIndex() { return Index; }

		// Function access operator
		T* operator->()
		{
			return Pool->GetPtr(Index);
		}

		// Dereference Operator
		const T operator*() const
		{
			return *Pool->GetPtr(Index);
		}

		// Returns the pointer
		T* AsPointer()
		{
			return Pool->GetPtr(Index);
		}

		// Common operators
		bool operator==(const VPoolPointer& other) { return **this == *other; }
		bool operator!=(const VPoolPointer& other) { return **this != *other; }
		bool operator<(const VPoolPointer& other) { return **this < *other; }
		bool operator>(const VPoolPointer& other) { return **this > *other; }
		bool operator<=(const VPoolPointer& other) { return **this <= *other; }
		bool operator>=(const VPoolPointer& other) { return **this >= *other; }
	};

	friend class VPoolPointer;
private:
	T* Data;	// Array of data

	uint32 MaxCount;	// Total number of allocated objects

	// Only callable by VPoolPointers
	inline T* GetPtr(uint32 index)
	{
		return &Data[index];
	}

public:
	VDynamicPool()
		: Data(nullptr),
		MaxCount(0)
	{
	}

	VDynamicPool(uint32 count)
		: Data(nullptr),
		MaxCount(0)
	{
		Resize(count);
	}

	~VDynamicPool()
	{
		if(Data) free(Data);
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
	}

	VPoolPointer Get(uint32 index)
	{
		if (index >= MaxCount)
			Resize(index + (index >> 1));

		return VPoolPointer(index, this);
	}

	// Getters
	inline uint32 GetMaxCount() { return MaxCount; }
	inline const T* GetFront() { return Data ? &Data[0] : nullptr; }
	inline const T* GetEnd() { return Data ? &Data[MaxCount] : nullptr; }
};