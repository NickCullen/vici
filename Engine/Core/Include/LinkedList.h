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
		:Head(nullptr)
	{
		Tail = Head = new ListItem();
	}

	~VLinkedList()
	{
		Empty();
		delete(Head);
	}

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

	void Add(const T& item)
	{
		Tail->Next = new ListItem();
		Tail->Next->Prev = Tail;
		Tail = Tail->Next;
		Tail->Data = item;
	}

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

	const ListItem* GetFirst()
	{
		return Head->Next;
	}

	const ListItem* GetNext(const ListItem* current)
	{
		return current ? current->Next : nullptr;
	}
};