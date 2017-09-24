#include "SharedPtr.h"
#include "gtest/gtest.h"

using namespace Core;

class TestClass
{
public:
    int TestData = 0;

};

TEST(TSharedPtr, DefaultConstructor) {
    TSharedPtr<TestClass> sp;

    EXPECT_EQ(sp.GetRefCount(), 1);
    EXPECT_TRUE((*sp) == nullptr);
}


TEST(TSharedPtr, DataConstructor) {
    TestClass* tc = new TestClass();
    tc->TestData = 22;

    TSharedPtr<TestClass> sp = tc;

    EXPECT_EQ(sp.GetRefCount(), 1);
    EXPECT_EQ(sp->TestData, 22);
}