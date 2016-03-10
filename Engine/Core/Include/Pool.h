#pragma once

#include "CoreAPI.h"
#include "VTypes.h"
#include <memory>

template <typename T>
class CORE_API VPool
{
protected:
	T* Data;	// Array of data

	uint32 MaxCount;	// Total number of allocated objects

public:
	VPool()
		: Data(nullptr),
		MaxCount(0)
	{
	}

	VPool(uint32 count)
		: Data(nullptr),
		MaxCount(0)
	{
		SetSize(count);
		ZeroMemory();
	}

	/**
	* Copy Constructor (we dont want to have 2 copies of a pool
	* pointing at the same pool. Consider passing pools by reference to
	* prevent this.
	*/
	VPool(const VPool& other)
	{
		uint32 size = other.MaxCount * sizeof(T);
		Data = (T*)malloc(size);
		memcpy(Data, other.Data, size);

		MaxCount = other.MaxCount;
	}

	~VPool()
	{
		if (Data) free(Data);
	}

	/**
	* Sets the size of the pool and allocates memory.
	* If Data is already set, it will be deleted and
	* the new data will be allocated at the given size
	* @param newCount How many T items to allocate, note that this is NOT the size in bytes
	*/
	void SetSize(uint32 newCount)
	{
		uint32 newSize = newCount * sizeof(T);
		// Costly op, dont do if we are resizing to the same size!
		if (newSize != MaxCount * sizeof(T))
		{
			// Data already exists
			if (Data != nullptr)
				free(Data);

			Data = (T*)malloc(newSize);
			MaxCount = newCount;
		}

	}


	/**
	* Shifts the elements on the pool from the given index
	* down one index. This will remove the element at the given index
	*/
	void ShiftDownFrom(uint32 index)
	{
		T* cutoff = &Data[index];		// The item we will be remove
		T* move = &Data[index + 1];		// Where we will move the item down from
		memcpy(cutoff, move, (MaxCount - index - 1) * sizeof(T));
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
	inline uint32 GetMaxCount() const { return MaxCount; }
	inline const T* GetFront() { return Data ? &Data[0] : nullptr; }
	inline const T* GetEnd() { return Data ? &Data[MaxCount] : nullptr; }
};