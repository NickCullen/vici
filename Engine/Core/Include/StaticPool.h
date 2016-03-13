#pragma once

#include "Pool.h"

/**
 * Unlike dynamic pool, this will remain
 * the given size unless specifically told otherwise.
 */
template<typename T>
class CORE_API VStaticPool : public VPool<T>
{
private:

public:
	VStaticPool()
		: VPool()
	{
	}

	VStaticPool(uint32 count)
		: VPool(count)
	{
	}

	/**
	* Copy Constructor (we dont want to have 2 copies of a pool
	* pointing at the same pool. Consider passing pools by reference to
	* prevent this.
	*/
	VStaticPool(const VStaticPool& other)
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
	VStaticPool& operator=(const VStaticPool<T>& other)
	{
		uint32 size = other.MaxCount * sizeof(T);
		Data = (T*)realloc(Data, size);
		memcpy(Data, other.Data, size);

		MaxCount = other.MaxCount;
		return *this;
	}

	T& operator[](int32 index)
	{
		return Data[index];
	}

	const T& operator[](int32 index) const
	{
		return Data[index];
	}

	T& Get(uint32 index)
	{
		return Data[index];
	}

	const T& Get(uint32 index) const
	{
		return Data[index];
	}

	void Set(uint32 index, const T& data)
	{
		Data[index] = data;
	}
};