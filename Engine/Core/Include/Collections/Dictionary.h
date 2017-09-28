#pragma once

#include "CoreTypes.h"
#include "Collections/Array.h"

namespace Core
{
	/**
	* Class to store values as a key,value pair
	*/
	template< typename KeyType, typename ValueType>
	class TDictionary
	{
		class TDictionaryEntry
		{
		public:
			KeyType Key;
			ValueType Val;

			TDictionaryEntry() = default;
			TDictionaryEntry(const KeyType& key, const ValueType& val)
				: Key(key),
				Val(val)
			{}
		};


	public:
		const static uint32 MAX_DICT_SIZE = 32;

	private:
		TArray<TDictionaryEntry> Entries[MAX_DICT_SIZE];

		uint32 Count = 0;

	public:
		TDictionary()
		{

		}

		~TDictionary()
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
			uint32 index = key % MAX_DICT_SIZE;
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
		* Operator [] for const objects 
		*/
		const ValueType& operator[](const KeyType& key) const
		{
			uint32 index = key % MAX_DICT_SIZE;
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
			uint32 index = key % MAX_DICT_SIZE;
			Entries[index].Add(TDictionaryEntry(key, val));
			Count++;
		}

		/**
		* Gets the data of the entry with the given key
		* @param key The key of the item to get
		* @param outVal Pointer to set if a value was found
		* @return Returns true if the item was found and set
		*/
		bool Get(const KeyType& key, ValueType& outVal) const
		{
			uint32 index = key % MAX_DICT_SIZE;
			for (uint32 i = 0; i < Entries[index].GetCount(); i++)
			{
				if (Entries[index][i].Key == key)
				{
					outVal = Entries[index][i].Val;
					return true;
				}
			}
			return false;
		}


		/**
		* Returns if there is an entry in the dict with the 
		* given key
		*/
		bool KeyExists(const KeyType& key) const
		{
			uint32 index = key % MAX_DICT_SIZE;
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
			uint32 index = key % MAX_DICT_SIZE;
			for (uint32 i = 0; i < Entries[index].GetCount(); i++)
			{
				if (Entries[index][i].Key == key)
				{
					Entries[index].Remove(i);
					Count--;
					return true;
				}
			}
			return false;
		}

		// Getters
		inline uint32 GetCount() { return Count; }

	};

}