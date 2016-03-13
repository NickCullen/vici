#pragma once

#include "CoreAPI.h"

template<typename T>
class CORE_API VStack
{
	class VStackNode
	{
	public:
		VStackNode* Next;	// Next item to appear in the stack
		T Data;

		VStackNode()
			:Next(nullptr)
		{}
	};
private:
	VStackNode* Head;
public:
	VStack()
		:Head(nullptr)
	{
	}

	~VStack()
	{
		Empty();
	}

	void Empty()
	{
		while (Head)
		{
			VStackNode* next = Head->Next;
			delete(Head);
			Head = next;
		}
	}


	/**
	 * Pushes an item on top of the stack
	 */
	void Push(const T& item)
	{
		VStackNode* newNode = new VStackNode;
		// >= 1 item
		if (Head)
		{
			VStackNode* next = Head;
			Head = newNode;
			Head->Next = next;
		}
		// Empty stack
		else
		{
			Head = newNode;
		}
		newNode->Data = item;
	}

	/**
	 * Gets the first element off the stack
	 * @param outVariable This variable will be set if item successfully popped
	 * @return Returns true/false depending on wether there was an item to pop off
	 */
	bool Pop(T& outVariable)
	{
		if (Head)
		{
			VStackNode* dataNode = Head;
			outVariable = dataNode->Data;
			Head = Head->Next;
			delete(dataNode);
			return true;
		}
		return false;
	}

	/**
	 * Similar to pop except it will not remove the value
	 * @param outVariable This variable will be set if an item exists
	 * @return Returns true/false if there was an item to peek at or not
	 */
	bool Peek(T& outVariable) const
	{
		if (Head)
		{
			outVariable = Head->Data;
			return true;
		}
		return false;
	}
};