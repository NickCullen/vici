#pragma once

#include "CoreAPI.h"
#include "Reflection/Class.h"
#include "Reflection/ClassManager.h"
#include "Reflection/Type.h"
#include "VString.h"

namespace Core
{
    template<typename ClassT>
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
                  ClassPtr->Size = sizeof(ClassT);
            }
        }


        template<typename P>
        VClassTypeConstructor<ClassT>& AddProperty(const VString& PropertyName, P PropertyAccessor)
        {
            VProperty* p = new VProperty(PropertyName, VType(ValueTypeMapper<P>::Value));
            if(ClassPtr)
            {
                ClassPtr->Properties.Add(p);
            }

            return *this;
        }


        VClass* GetClassPtr() { return ClassPtr; }
      
    };
}