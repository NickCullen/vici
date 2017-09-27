#pragma once

#include "CoreAPI.h"
#include "Collections/Dictionary.h"
#include "VString.h"

namespace Core
{
    class VClass;

    class CORE_API VClassManager
    {
        typedef TDictionary<VString, VClass*> ClassDict;

    private:
        ClassDict ConstructedClasses;

        VClassManager(){}
    public:
        static VClassManager* GetInstance();

        /**
         * Will create a class pointer with the given name,
         * If the class already exists, it will return nullptr
         * as this enforces a strict rule that classes cannot
         * be modified after they have been created once!
         */
        VClass* CreateClassPointer(const VString& ClassName);

        /**
         * Returns the class with the given name
         */
        VClass* GetClass(const VString& ClassName) const;
    };
}