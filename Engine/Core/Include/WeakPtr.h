#pragma once

#include "SharedPtr.h"
#include "WeakPtrBase.h"

namespace Core
{
    template<typename T>
    class TWeakPtr : public IWeakPtrBase
    {
    private:
        TSharedPtr<T>* SharedPointerRef = nullptr;

    public:
        
        /**
         * Default Constructor
         */
        TWeakPtr() : IWeakPtrBase()
        {
            
        }

        /**
         * Copy Constructor
         */
        TWeakPtr(const TWeakPtr<T>& other)
        {
            SharedPointerRef = other.SharedPointerRef;
            if(SharedPointerRef)
            {
                SharedPointerRef->AddWeakReferencePtr(this);
            }
        }

        /**
         * Overloaded Constructor
         */
        TWeakPtr(TSharedPtr<T>& sp)
        {
            SharedPointerRef = &sp;
            SharedPointerRef->AddWeakReferencePtr(this);
        }

        ~TWeakPtr()
        {
            ClearReference();   // Clear old ref if exists
        }

        /**
         * Overloaded assignment operator
         * for shared pointer
         */
        TWeakPtr<T>& operator = (TSharedPtr<T>& sp)
        {
            // Avoid self assignment
            if (SharedPointerRef != &sp) 
            {
                ClearReference();   // Clear old ref if exists
                
                SharedPointerRef = &sp;
                SharedPointerRef->AddWeakReferencePtr(this);
            }
            return *this;
        }

        /**
         * Overloaded assignment operator
         * for another weak pointer
         */
        TWeakPtr<T>& operator = (const TWeakPtr<T>& other)
        {
            // Avoid self assignment
            if (this != &other) 
            {
                ClearReference();   // Clear old ref if exists
                
                SharedPointerRef = other.SharedPointerRef;
                if(SharedPointerRef != nullptr)
                {
                    SharedPointerRef->AddWeakReferencePtr(this);
                }
            }
            return *this;
        }

        /**
         * Determine if this weak pointer is valid
         */
        operator bool() const
        {
            return bIsValid;
        }

        /**
         * Dereference operator
         */
        T* operator* () const
        {
            return bIsValid ? SharedPointerRef->Ptr : nullptr;
        }

        /**
         * Pointer memory accessor override
         */
        T* operator-> () const
        {
            return bIsValid ? SharedPointerRef->Ptr : nullptr;
        }

        /**
         * Clears reference to pointer
         */ 
        void ClearReference()
        {
            if(SharedPointerRef != nullptr)
            {
                SharedPointerRef->RemoveWeakReferencePtr(this);
                SharedPointerRef = nullptr;
            }
        }

        /**
         * Override
         */
        virtual void Invalidate()
        {
            IWeakPtrBase::Invalidate();
            SharedPointerRef = nullptr;
        }
    };
}