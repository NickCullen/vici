#pragma once

#include "CoreAPI.h"
#include "CoreTypes.h"

namespace Core
{
    class CORE_API RefCounter
    {
    private:
        uint32 Count = 0;
    
    public:
    
        inline void AddRef() { Count++; }
        inline uint32 RemoveRef() { return --Count;}
        inline uint32 GetCount() { return Count; }
    };
}
