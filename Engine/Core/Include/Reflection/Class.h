#pragma once

#include "CoreAPI.h"
#include "CoreTypes.h"
#include "Collections/Array.h"
#include "VString.h"
#include "Reflection/Property.h"

namespace Core
{
    template<typename T>
    class VClassTypeConstructor;
    
    class CORE_API VClass
    {
        template<typename T>
        friend class VClassTypeConstructor;

        typedef TArray<VProperty> PropertyList;

    private:
        VString Name;

        uint32 Size;

        //PropertyList Properties;

    public:

       
        VString GetName() { return Name; }
        uint32 GetSize() { return Size; }
    };
}