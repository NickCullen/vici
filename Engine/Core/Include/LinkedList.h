#pragma once

#include "CoreAPI.h"

template<typename T>
class CORE_API VLinkedList
{
	struct ListItem
	{
		ListItem* Next;
		ListItem* Prev;
		mutable T Data;

		ListItem()
			: Next(nullptr),
			Prev(nullptr)
		{}
	};

private:
	ListItem* Head;
	ListItem* Tail;
public:
	VLinkedList()
		:Head(nullptr),
		Tail(nullptr)
	{
		Tail = Head = new ListItem();
	}

	~VLinkedList()
	{
		Empty();
		delete(Head);
	}

	/**
	 * Empties the list, leaving data untouched
	 */
	void Empty()
	{
		ListItem* current = Head->Next;
		while (current)
		{
			ListItem* next = current->Next;
			delete(current);
			current = next;
		}
	}

	/**
	 * Add specified item to the end of list
	 */
	void Add(const T& item)
	{
		Tail->Next = new ListItem();
		Tail->Next->Prev = Tail;
		Tail = Tail->Next;
		Tail->Data = item;
	}

	/**
	 * Remove the item from the list
	 * Note that this will search from start 
	 * to end until it finds the item
	 */
	bool Remove(const T& item)
	{
		ListItem* current = Head->Next;
		while (current)
		{
			if (current->Data == item)
				return Remove(current);
			else
				current = current->Next;
		}
		return false;
	}

	/**
	 * Removes the item from the list, this will be
	 * carried out in constant time
	 */
	bool Remove(ListItem* item)
	{
		if (item != Head)
		{
			item->Prev->Next = item->Next;
			if (item->Next)
				item->Next->Prev = item->Prev;
			delete (item);
			return true;
		}
		return false;
	}

	/**
	 * Returns the first item on the list
	 * may be nullptr
	 */
	const ListItem* GetFirst()
	{
		return Head->Next;
	}

	/** 
	 * Gets the next item given the current
	 */
	const ListItem* GetNext(const ListItem* current)
	{
		return current ? current->Next : nullptr;
	}

	/**
	 * Returns the tail of the list
	 */
	const ListItem* GetLast()
	{
		return Tail != Head ? Tail : nullptr;
	}

	/**
	 * gets the previous item from the current
	 */
	const ListItem* GetPrevious(const ListItem* current)
	{
		return current && current->Prev != Head ? current->Prev : nullptr;
	}
};