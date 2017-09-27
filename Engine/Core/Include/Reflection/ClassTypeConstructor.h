#pragma once

#include "CoreAPI.h"
#include "Reflection/Class.h"
#include "Reflection/ClassManager.h"
#include "VString.h"

namespace Core
{
    template<typename T>
    class VClassTypeConstructor
    {
    private:
        VClass* ClassPtr;

    public:
        VClassTypeConstructor(const VString& ClassName)
        {
            ClassPtr = VClassManager::GetInstance()->CreateClassPointer(ClassName);
            if(ClassPtr)
            {
                  ClassPtr->Name = ClassName;
                  ClassPtr->Size = sizeof(T);
            }
        }




        VClass* GetClassPtr() { return ClassPtr; }
      
    };
}