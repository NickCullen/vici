#include "gtest/gtest.h"
#include "Reflection/Object.h"
#include <stdio.h>

#include "Reflection/ClassTypeConstructor.h"

using namespace Core;

class TestClass : public VObject
{
private:
    uint32 MyInt = 20;

    uint32 MyInt2 = 40;
public:

    virtual const VClass* GetClass(){ return nullptr; }
};

TEST(WIP_ReflectionTests, ClassCreation)
{
    auto constructor = VClassTypeConstructor<TestClass>("TestClass");

    VClass* ptr = constructor.GetClassPtr();

    VClass* ptr2 = VClassManager::GetInstance()->GetClass("TestClass");
}