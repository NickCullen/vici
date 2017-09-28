#pragma once

#include "CoreAPI.h"
namespace Core
{
    class VClass;

    class VObject
    {
    public:
        virtual const VClass* GetClass() = 0; 
    };
}
