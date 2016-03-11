#pragma once

#include "CoreAPI.h"
#include "Hash.h"
#include "LinkedList.h"
#include "Array.h"

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
	//VLinkedList<VDictionaryEntry> Entries[MAX_DICT_SIZE];	// Array of linked lists set to MAX_DICT_SIZE
	VArray<VDictionaryEntry> Entries[MAX_DICT_SIZE];

public:
	VDictionary()
	{

	}

	~VDictionary()
	{

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

};