#pragma once

#include "CoreTypes.h"

namespace Core
{
	template<typename T>
	class TStack
	{
		class TStackNode
		{
		public:
			TStackNode* Next;	// Next item to appear in the stack
			T Data;

			TStackNode()
				:Next(nullptr)
			{}
		};
	private:
		TStackNode* Head;

		uint32 Count = 0;

	public:
		TStack()
			:Head(nullptr)
		{
		}

		~TStack()
		{
			Clear();
		}

		void Clear()
		{
			while (Head)
			{
				TStackNode* next = Head->Next;
				delete(Head);
				Head = next;
			}
			Count = 0;
		}


		/**
		* Pushes an item on top of the stack
		*/
		void Push(const T& item)
		{
			TStackNode* newNode = new TStackNode;
			// >= 1 item
			if (Head)
			{
				TStackNode* next = Head;
				Head = newNode;
				Head->Next = next;
			}
			// Empty stack
			else
			{
				Head = newNode;
			}
			newNode->Data = item;
			Count++;
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
				TStackNode* dataNode = Head;
				outVariable = dataNode->Data;
				Head = Head->Next;
				delete(dataNode);
				Count--;
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

		inline uint32 GetCount() { return Count; }
	};

}