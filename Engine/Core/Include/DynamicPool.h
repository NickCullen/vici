#pragma once

#include "Pool.h"

// Forward decl. friends
template<typename T> 
class VArray;

/**
 * Pool of objects that can resize if
 * a call to Get exceeds MaxCount
 */
template<typename T>
class CORE_API VDynamicPool : public VPool<T>
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
		T& operator*()
		{
			return Pool->GetData(Index);
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
	friend class VArray<T>;

private:
	
	// Only callable by VPoolPointers
	inline T* GetPtr(uint32 index)
	{
		return &Data[index];
	}

	inline T& GetData(uint32 index)
	{
		return Data[index];
	}

public:
	VDynamicPool()
		: VPool()
	{
	}

	VDynamicPool(uint32 count)
		: VPool(count)
	{
	}

	// Resizes array to the newCount * sizeof(T)
	void Resize(uint32 newCount)
	{
		uint32 newSize = newCount * sizeof(T);
		// Costly op, dont do if we are resizing to the same size!
		if (newSize != MaxCount * sizeof(T))
		{
			// Data already exists
			if (Data != nullptr)
				Data = (T*)realloc(Data, newSize);
			else
				Data = (T*)malloc(newSize);

			MaxCount = newCount;
		}
	}

	VPoolPointer operator[](int32 index)
	{
		return Get(index);
	}

	VPoolPointer Get(uint32 index)
	{
		if (index >= MaxCount)
			Resize(index + (index >> 1));

		return VPoolPointer(index, this);
	}

	void Set(uint32 index, const T& data)
	{
		if (index >= MaxCount)
			Resize(index + (index >> 1));

		Data[index] = data;
	}
};