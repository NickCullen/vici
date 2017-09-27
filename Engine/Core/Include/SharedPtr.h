#pragma once

#include "RefCounter.h"
#include "Collections/Array.h"
#include "WeakPtrBase.h"

namespace Core
{
    // Forward decl.
    template<typename T>
    class TWeakPtr;

    template<typename T>
    class TSharedPtr
    {
        friend class TWeakPtr<T>;
    private:
        T* Ptr = nullptr;       /**< Native pointer to data */

        RefCounter* Counter = nullptr;      /**< Refernce counter to data */

        TArray<IWeakPtrBase*>* WeakReferences;    /**< An array of weak references to this shared pointer */

    public:

        TSharedPtr()
        {
            Counter = new RefCounter();
            Counter->AddRef();
            WeakReferences = new TArray<IWeakPtrBase*>();
        }

        TSharedPtr(T* ptr)
            : Ptr(ptr)
        {
            Counter = new RefCounter();
            Counter->AddRef();
            WeakReferences = new TArray<IWeakPtrBase*>();
        }

        /**
        * Copy constructor 
        */
        TSharedPtr(const TSharedPtr<T>& Other)
            : Ptr(Other.Ptr),
            Counter(Other.Counter),
            WeakReferences(Other.WeakReferences)
        {
            Counter->AddRef();
        }

        /**
        * Destructor - delete object, if no more
        * references exist
        */
        ~TSharedPtr()
        {
            if(Counter != nullptr && Counter->RemoveRef() == 0)
            {
                Erase(); 
            }
        }

        /**
        * Dereference operator
        */
        T* operator* () const
        {
            return Ptr;
        }

        /**
        * Pointer memory accessor override
        */
        T* operator-> () const
        {
            return Ptr;
        }

        /**
        * Overloaded assignment operator
        * this excludes self assignment 
        */
        TSharedPtr<T>& operator = (const TSharedPtr<T>& Other)
        {
            // Avoid self assignment
            if (this != &Other) 
            {
                // Decrement the old reference count in THIS
                // if reference become zero delete the old data
                if(Counter->RemoveRef() == 0)
                {
                    Erase();
                }

                // Copy the data and reference pointer
                // and increment the reference count
                Ptr = Other.Ptr;
                Counter = Other.Counter;
                if(Counter != nullptr)
                    Counter->AddRef();
                WeakReferences = Other.WeakReferences;
            }
            return *this;
        }

        /**
         * Clears reference to pointer
         */ 
        void ClearReference()
        {
            if(Counter->RemoveRef() == 0)
            {
                Erase();
            }

            Ptr = nullptr;
            Counter = nullptr;
            WeakReferences = nullptr;
        }

        /**
         * Determine if this shared pointer is valid
         */
        operator bool() const
        {
            return Ptr != nullptr;
        }

        inline uint32 GetRefCount() const
        {
            return Counter != nullptr ? Counter->GetCount() : 0;
        }

        inline uint32 GetWeakRefCount() const
        {
            return WeakReferences != nullptr ? WeakReferences->GetCount() : 0;
        }

    protected:
        void Erase()
        {
            delete Ptr;
            delete Counter;

            // Invalidate all weak references which point to here
            for(uint32 i = 0; i < WeakReferences->GetCount(); i++)
            {
                (*WeakReferences)[i]->Invalidate();
            }
            delete WeakReferences;
        }

        void AddWeakReferencePtr(IWeakPtrBase* weakPtr)
        {
            WeakReferences->Add(weakPtr);
            weakPtr->Validate();
        }

        void RemoveWeakReferencePtr(IWeakPtrBase* weakPtr)
        {
            WeakReferences->RemoveItem(weakPtr);
            weakPtr->Invalidate();
        }

    };
}