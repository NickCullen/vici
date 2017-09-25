#pragma once

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
	public:
		TQueue()
		{
			Head = Tail = new TQueueItem();
		}

		~TQueue()
		{
			Empty();
			delete(Head);
		}

		/**
		* Empties queue, leaving Data untouched
		*/
		void Empty()
		{
			while (Head->Next)
			{
				TQueueItem* next = Head->Next;
				Head->Next = next->Next;
				delete(next);
			}
			Tail = Head;
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
		}
	};
}