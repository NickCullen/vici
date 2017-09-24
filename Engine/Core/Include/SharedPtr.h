#pragma once

#include "RefCounter.h"

namespace Core
{
    template<typename T>
    struct TSharedPtr
    {
    private:
        T* Ptr = nullptr;       /**< Native pointer to data */

        RefCounter* Counter = nullptr;      /**< Refernce counter to data */

    public:

        TSharedPtr()
        {
            Counter = new RefCounter();
            Counter->AddRef();
        }

        TSharedPtr(T* ptr)
            : Ptr(ptr)
        {
            Counter = new RefCounter();
            Counter->AddRef();
        }

        /**
        * Copy constructor 
        */
        TSharedPtr(const TSharedPtr<T>& Other)
            : Ptr(Other.Ptr),
            Counter(Other.Counter)
        {
            Counter->AddRef();
        }

        /**
        * Destructor - delete object, if no more
        * references exist
        */
        ~TSharedPtr()
        {
            if(Counter->RemoveRef() == 0)
            {
                Erase(); 
            }
        }

        /**
        * Dereference operator
        */
        T* operator* ()
        {
            return Ptr;
        }

        /**
        * Pointer memory accessor override
        */
        T* operator-> ()
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
                Counter->AddRef();
            }
            return *this;
        }

        uint32 GetRefCount()
        {
            return Counter->GetCount();
        }

    private:
        void Erase()
        {
            delete Ptr;
            delete Counter;
        }
    };
}