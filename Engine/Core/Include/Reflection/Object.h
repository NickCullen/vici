#pragma once

#include "CoreAPI.h"
namespace Core
{
    class VClass;

    class CORE_API VObject
    {
    public:
        virtual const VClass* GetClass() = 0; 
    };
}
