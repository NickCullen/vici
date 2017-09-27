#include "Reflection/ClassManager.h"
#include "Reflection/Class.h"

using namespace Core;

VClassManager* VClassManager::GetInstance()
{
    static VClassManager cm;
    return &cm;
}

VClass* VClassManager::CreateClassPointer(const VString& ClassName)
{
    if(!ConstructedClasses.KeyExists(ClassName))
    {
        VClass* Ptr = new VClass();

        ConstructedClasses.Insert(ClassName, Ptr);

        return Ptr;
    }
    else
        return nullptr;
}

VClass* VClassManager::GetClass(const VString& ClassName) const
{
    return ConstructedClasses.KeyExists(ClassName) ? ConstructedClasses[ClassName] : nullptr;
}