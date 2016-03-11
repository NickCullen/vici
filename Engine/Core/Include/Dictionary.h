#pragma once

#include "CoreAPI.h"
#include "Hash.h"
#include "Array.h"

/**
 * Class to store values as a key,value pair
 */
template< typename ValueType, typename KeyType = VHash>
class CORE_API VDictionary
{
	class VDictionaryEntry
	{
	public:
		KeyType Key;
		ValueType Val;

		VDictionaryEntry() = default;
		VDictionaryEntry(const KeyType& key, const ValueType& val)
			: Key(key),
			Val(val)
		{}
	};


public:
	const static int MAX_DICT_SIZE = 32;

private:
	VArray<VDictionaryEntry> Entries[MAX_DICT_SIZE];

public:
	VDictionary()
	{

	}

	~VDictionary()
	{

	}

	/**
	 * Access an element like an array, will throw error if no entry exists
	 * Note that if Dictionary is being used as a pointer
	 * remember to derefence it before using [] operator like so
	 * (*dict)[<id>]
	 */
	ValueType& operator[](const KeyType& key)
	{
		uint32 index = key.Value() % MAX_DICT_SIZE;
		for (uint32 i = 0; i < Entries[index].GetCount(); i++)
		{
			if (Entries[index][i].Key == key)
			{
				return Entries[index][i].Val;
			}
		}
		
		throw "Entry does not exist";
	}

	/**
	 * Insert the value with the given key in the dict
	 */
	void Insert(const KeyType& key, const ValueType& val)
	{
		int index = key.Value() % MAX_DICT_SIZE;
		Entries[index].Add(VDictionaryEntry(key, val));
	}

	/**
	 * Gets the data of the entry with the given key
	 * @param key The key of the item to get
	 * @param outVal Pointer to set if a value was found
	 * @return Returns true if the item was found and set
	 */
	bool Get(const KeyType& key, ValueType* outVal)
	{
		uint32 index = key.Value() % MAX_DICT_SIZE;
		for (uint32 i = 0; i < Entries[index].GetCount(); i++)
		{
			if (Entries[index][i].Key == key)
			{
				*outVal = Entries[index][i].Val;
				return true;
			}
		}
		return false;
	}

	/**
	 * Returns if there is an entry in the dict with the 
	 * given key
	 */
	bool KeyExists(const KeyType& key)
	{
		uint32 index = key.Value() % MAX_DICT_SIZE;
		for (uint32 i = 0; i < Entries[index].GetCount(); i++)
		{
			if (Entries[index][i].Key == key)
				return true;
		}
		return false;
	}

	/**
	 * Removes the item with the given key
	 * Will return true if successfully removed
	 */
	bool Remove(const KeyType& key)
	{
		uint32 index = key.Value() % MAX_DICT_SIZE;
		for (uint32 i = 0; i < Entries[index].GetCount(); i++)
		{
			if (Entries[index][i].Key == key)
			{
				Entries[index].RemoveAt(i);
				return true;
			}
		}
		return false;
	}

};