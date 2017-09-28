#pragma once

#include "CoreAPI.h"
#include "Reflection/Type.h"
#include "VString.h"

namespace Core
{
    class CORE_API VProperty
    {
    private:
        VType Type;

        VString Name;
    public:
        VProperty(const VString& name, const VType& type)
        {
            Name = name;
            Type = type;
        }

        inline VType GetType()
        {
            return Type;
        }

        inline VString GetName()
        {
            return Name;
        }
    };
}