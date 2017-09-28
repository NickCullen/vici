#include "gtest/gtest.h"
#include "Reflection/Object.h"
#include <stdio.h>

#include "Reflection/ClassTypeConstructor.h"

using namespace Core;

class TestClass : public VObject
{
public:
    int MyInt = 20;

    int MyInt2 = 40;
public:

    virtual const VClass* GetClass(){ return nullptr; }
};


TEST(Reflection, ClassBuilder)
{

    VType t1 = typeof(int);
    VType r3 = typeof(VString);

    auto c = VClassTypeConstructor<TestClass>("TestClass")
        .AddProperty("MyInt", &TestClass::MyInt);


    auto ptr = c.GetClassPtr();

    int i = 0;
    i++;
}