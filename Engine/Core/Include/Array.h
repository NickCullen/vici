#pragma once

#include "DynamicPool.h"

/**
 * Dynamic array class which 
 * have inline data elements to prevent
 * cache misses when iterating over list
 * similar behaviour as a std vector
 */
template <typename T>
class CORE_API VArray
{
private:
	VDynamicPool<T> Elements;		// Elements in the array

	uint32 Count;		// Number of elements in the array
public:
	const static int DEFAULT_MAX_SIZE = 5;

	/**
	 * Constructor
	 * @param initialCapacity Inital size of the pool, 5 default
	 */
	VArray(uint32 initialCapacity = DEFAULT_MAX_SIZE)
		:Count(0)
	{
		Elements.Resize(initialCapacity);
	}
	
	/**
	 * Array Index operator
	 */
	T& operator[](uint32 index)
	{
		return Elements.GetData(index);
	}

	/**
	 * Add an item at the end of the array
	 * @param element The element to add
	 */
	void Add(const T& element)
	{
		Elements.Set(Count++, element);
	}

	/**
	 * Remove the element at the given index
	 */
	void RemoveAt(uint32 index)
	{
		if (index < Count)
		{
			Elements.ShiftDownFrom(index);
			Count--;
		}
	}

	/**
	 * Remove all elements from the array and reduce pool down 
	 * to the default size
	 */
	void RemoveAll()
	{
		if (Count > 0)
		{
			Count = 0;
			Elements.Resize(DEFAULT_MAX_SIZE);
			Elements.ZeroMemory();
		}
	}

	/**
	 * Remove all elements after the given index
	 * @param index The index to remove elements after. Note this index is exclusive and will remain in the array
	 */
	void RemoveAllAfter(uint32 index)
	{
		// Dont actually need to do any realloc from here, just set Count to index size
		if (index+1 < Count)
		{
			Count = index+1;	
		}
	}

	/**
	* Remove all elements before the given index
	* @param index The index to remove elements before. Note this index is exclusive and will remain in the array
	*/
	void RemoveAllBefore(uint32 index)
	{
		if (index-1 < Count)
		{
			Elements.ShiftDownNTimesFrom(0, index);
			Count = Count - index;
		}
	}

	/**
	 * Removes the last element and returns it
	 */
	T& PopBack()
	{
		return Elements.GetData(--Count);
	}

	/**
	 * Returns a copy of the array, it is upto the caller
	 * to free this data
	 */
	T* GetDataCopy()
	{
		T* buff = (T*)malloc(Count*sizeof(T));
		Elements.CopyTo(buff, 0, Count);
		return buff;
	}

	// getters
	inline uint32 GetCount() { return Count; }
	inline uint32 GetSize() { return Count * sizeof(T); }
	inline uint32 GetCapacity() { return Elements.GetMaxCount(); }
	inline const T* GetData() { return Elements.Data; }
};