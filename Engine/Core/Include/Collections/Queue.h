#pragma once

#include "CoreTypes.h"

namespace Core
{
	/**
	* Queue datastructure that is FIFO
	*/
	template <typename T>
	class TQueue
	{
		class TQueueItem
		{
		public:
			TQueueItem* Next;	// Next item after this to get
			T Data;			// The data
		};

	private:
		TQueueItem* Head;	// Head of the queue (the first)
		TQueueItem* Tail;
		
		uint32 Count = 0;	// Number of items

	public:
		TQueue()
		{
			Head = Tail = new TQueueItem();
		}

		~TQueue()
		{
			Clear();
			delete(Head);
		}

		/**
		* Empties queue, leaving Data untouched
		*/
		void Clear()
		{
			while (Head->Next)
			{
				TQueueItem* next = Head->Next;
				Head->Next = next->Next;
				delete(next);
			}
			Tail = Head;
			Count = 0;
		}
		/**
		* Gets the first item in the queue and sets it to outData
		* @param outData The value to be set
		* @return Returns true if an item was taken off the queue, false if not and outData will not be set
		*/
		bool Get(T& outData)
		{
			if (Tail != Head)
			{
				TQueueItem* curItem = Head->Next;
				outData = curItem->Data;
				Head->Next = curItem->Next;
				if (Tail == curItem)
					Tail = Head;
				delete (curItem);
				Count--;
				return true;
			}
			return false;
		}

		/**
		* Adds the item onto the queue
		* @param item The item to be added
		*/
		void Add(const T& item)
		{
			Tail->Next = new TQueueItem();
			Tail->Next->Data = item;
			Tail = Tail->Next;
			Count++;
		}

		/**
		 * Returns number of items on Queue
		 */
		inline uint32 GetCount() { return Count; }
	};
}