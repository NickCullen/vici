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

	T& operator[](int32 index)
	{
		return Data[index];
	}

	T& Get(uint32 index)
	{
		return Data[index];
	}

	void Set(uint32 index, const T& data)
	{
		Data[index] = data;
	}
};