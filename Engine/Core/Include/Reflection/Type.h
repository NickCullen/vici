#pragma once

#include "CoreAPI.h"

namespace Core
{
    enum class CORE_API EValueType
    {
        None,       
        Boolean,   
        Integer,    
        Real,       
        String,     
        Enum,       
        Array,      
        User        
    };  
}