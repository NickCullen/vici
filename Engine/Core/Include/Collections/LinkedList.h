#pragma once

namespace Core
{
	/** 
	* Dynamic class data structure ideal for chains of
	* items which do not change often. If using for an
	* array of items, consider VArray
	*/
	template<typename T>
	class TLinkedList
	{
		struct TListItem
		{
			TListItem* Next;
			TListItem* Prev;
			mutable T Data;

			TListItem()
				: Next(nullptr),
				Prev(nullptr)
			{}

			// Dereference Operator
			T& operator*()
			{
				return Data;
			}

			const T& operator*() const
			{
				return Data;
			}
		};

		struct TListItemIterator
		{
			TListItem* Current;

			TListItemIterator(TListItem* current)
			{
				Current = current;
			}

			T& operator*()
			{
				return Current->Data;
			}

			void operator++()
			{
				Current = Current->Next;
			}

			bool operator!=(const TListItemIterator& It)
			{
				return (Current != It.Current);
			}
		};

	private:
		TListItem* Head;
		TListItem* Tail;
	public:
		TLinkedList()
			:Head(nullptr),
			Tail(nullptr)
		{
			Tail = Head = new TListItem();
		}

		~TLinkedList()
		{
			Empty();
			delete(Head);
		}

		/**
		* Empties the list, leaving data untouched
		*/
		void Empty()
		{
			TListItem* current = Head->Next;
			while (current)
			{
				TListItem* next = current->Next;
				delete(current);
				current = next;
			}
			Tail = Head;	// Move back.
			Head->Next = nullptr;
		}

		/**
		* Add specified item to the end of list
		*/
		void Add(const T& item)
		{
			Tail->Next = new TListItem();
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
			TListItem* current = Head->Next;
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
		bool Remove(TListItem* item)
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
		const TListItem* GetFirst() const
		{
			return Head->Next;
		}

		/** 
		* Gets the next item given the current
		*/
		const TListItem* GetNext(const TListItem* current) const
		{
			return current ? current->Next : nullptr;
		}

		/**
		* Returns the tail of the list
		*/
		const TListItem* GetLast() const
		{
			return Tail != Head ? Tail : nullptr;
		}

		/**
		* gets the previous item from the current
		*/
		const TListItem* GetPrevious(const TListItem* current) const
		{
			return current && current->Prev != Head ? current->Prev : nullptr;
		}

		// For support with C++11 foreach loop
		TListItemIterator begin() { return TListItemIterator((TListItem*)GetFirst()); }
		TListItemIterator end() { return TListItemIterator(nullptr);  }
	};
}