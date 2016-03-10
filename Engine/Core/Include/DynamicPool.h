#pragma once

#include "CoreAPI.h"
#include "VTypes.h"
#include <memory>

// Forward decl. friends
template<typename T> 
class VArray;

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
	T* Data;	// Array of data

	uint32 MaxCount;	// Total number of allocated objects

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

	/**
	 * Copy Constructor (we dont want to have 2 copies of a dynamic pool
	 * pointing at the same pool. Consider passing pools by reference to 
	 * prevent this.
	 */
	VDynamicPool(const VDynamicPool& other)
	{
		uint32 size = other.MaxCount * sizeof(T);
		Data = (T*)malloc(size);
		memcpy(Data, other.Data, size);

		MaxCount = other.MaxCount;
	}
	~VDynamicPool()
	{
		if(Data) free(Data);
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

	/**
	 * Shifts the elements on the pool from the given index
	 * down one index. This will remove the element at the given index
	 */
	void ShiftDownFrom(uint32 index)
	{
		T* cutoff = &Data[index];		// The item we will be remove
		T* move = &Data[index + 1];		// Where we will move the item down from
		memcpy(cutoff, move, (MaxCount - index -1 ) * sizeof(T));
	}

	/**
	 * Shifts down N given times from the given index. This will remove
	 * the values before and including the given index
	 */
	void ShiftDownNTimesFrom(uint32 index, uint32 nTimes) 
	{
		T* cutoff = &Data[index];			// Start of items to remove
		T* move = &Data[index + nTimes];	// Start of the first value we are going to keep
		memcpy(cutoff, move, (MaxCount - index - nTimes) * sizeof(T));
	}

	/**
	 * Copies the elements from and to specified indices
	 * to the given buffer.
	 * @param buffer The pre-allocated buffer
	 * @param start The start index (inclusive)
	 * @param end The end index (inclusive)
	 */
	void CopyTo(T* buffer, uint32 start, uint32 end)
	{
		T* begin = &Data[start];
		memcpy(buffer, begin, (end - start) * sizeof(T));
	}

	/**
	 * Zeros out the allocated memory
	 */
	void ZeroMemory()
	{
		memset(Data, 0, MaxCount * sizeof(T));
	}
	// Getters
	inline uint32 GetMaxCount() { return MaxCount; }
	inline const T* GetFront() { return Data ? &Data[0] : nullptr; }
	inline const T* GetEnd() { return Data ? &Data[MaxCount] : nullptr; }
};