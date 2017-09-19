#pragma once

#include "Pool.h"

/**
 * Pool of objects that can resize if
 * a call to Get exceeds MaxCount
 */
template<typename T>
class TDynamicPool : public VPool<T>
{
	/**
	 * Use for safe access when working with dynamic pools
	 */
	class VPoolPointer
	{
		friend class TDynamicPool;
	private:
		uint32 Index;		// Index into Pool array
		TDynamicPool* Pool;	// Pointer to the pool so we can retrieve the object

		// Only pool object allowed to create these
		VPoolPointer(uint32 index, TDynamicPool* pool)
			:Index(index),
			Pool(pool)
		{}
		
	public:
		~VPoolPointer() = default;

		int GetIndex() const { return Index; }

		// Function access operator
		T* operator->() const
		{
			return Pool->GetPtr(Index);
		}

		// Dereference Operator
		T& operator*() const
		{
			return Pool->GetData(Index);
		}

		// Returns the pointer
		T* AsPointer() const
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

public:
	TDynamicPool()
		: VPool()
	{
	}

	TDynamicPool(uint32 count)
		: VPool(count)
	{
	}

	/**
	* Copy Constructor (we dont want to have 2 copies of a pool
	* pointing at the same pool. Consider passing pools by reference to
	* prevent this.
	*/
	TDynamicPool(const TDynamicPool<T>& other)
	{
		uint32 size = other.MaxCount * sizeof(T);
		Data = (T*)malloc(size);
		memcpy(Data, other.Data, size);

		MaxCount = other.MaxCount;
	}

	/**
	 * Same reason as copy constructor except we want to use realloc
	 * instead of malloc
	 */
	TDynamicPool& operator=(const TDynamicPool<T>& other)
	{
		uint32 size = other.MaxCount * sizeof(T);
		Data = (T*)realloc(Data,size);
		memcpy(Data, other.Data, size);

		MaxCount = other.MaxCount;
		return *this;
	}

	inline T* GetPtr(uint32 index) const
	{
		return &Data[index];
	}

	inline T& GetData(uint32 index) const
	{
		return Data[index];
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

	T& operator[](int32 index)
	{
		return Data[index];
	}

	const T& operator[](int32 index) const
	{
		return Data[index];
	}

	VPoolPointer Get(uint32 index) const
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
	 * Copy 'count' number of items from in to Data
	 * @param in The data to be copied into this pool
	 * @param count Number of elements of in to copy (note this is count, NOT size in bytes)
	 */
	void CopyFrom(const T* in, uint32 count)
	{
		if (count > MaxCount)
			Resize(count);

		memcpy(Data, in, count * sizeof(T));
	}
};