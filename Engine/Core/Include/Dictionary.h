#pragma once

#include "CoreAPI.h"
#include "Hash.h"
#include "LinkedList.h"

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
	const static int MAX_DICT_SIZE = 128;

private:
	VLinkedList<VDictionaryEntry> Entries[MAX_DICT_SIZE];	// Array of linked lists set to MAX_DICT_SIZE

public:
	VDictionary()
	{

	}

	~VDictionary()
	{

	}

	void Insert(const KeyType& key, const ValueType& val)
	{
		int index = key.Value() % MAX_DICT_SIZE;
		Entries[index].Add(VDictionaryEntry(key, val));
	}

};