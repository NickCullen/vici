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

TEST(TSharedPtr, CopyConstructor) {
    TestClass* tc = new TestClass();
    tc->TestData = 22;

    TSharedPtr<TestClass> sp1 = tc;
    TSharedPtr<TestClass> sp2 = sp1;

    EXPECT_EQ(sp1.GetRefCount(), 2);
    EXPECT_EQ(sp2.GetRefCount(), 2);

    EXPECT_TRUE(*sp1 != nullptr);
    EXPECT_TRUE(*sp2 != nullptr);
    EXPECT_TRUE(*sp1 == *sp2);
}

TEST(TSharedPtr, AssignmentOperator) {
    TestClass* tc1 = new TestClass();
    tc1->TestData = 22;

    TestClass* tc2 = new TestClass();
    tc2->TestData = 11;

    TSharedPtr<TestClass> sp1 = tc1;
    TSharedPtr<TestClass> sp2 = tc2;        

    sp2 = sp1;

    EXPECT_EQ(sp1.GetRefCount(), 2);
    EXPECT_EQ(sp2.GetRefCount(), 2);

    EXPECT_TRUE(*sp1 != nullptr);
    EXPECT_TRUE(*sp2 != nullptr);
    EXPECT_TRUE(*sp1 == *sp2);

    EXPECT_EQ(sp1->TestData, 22);
    EXPECT_EQ(sp2->TestData, 22);
}

TEST(TSharedPtr, ClearRefernce)
{
    TSharedPtr<TestClass> sp = new TestClass();   
    
    EXPECT_TRUE(sp);
    
    sp.ClearReference();

    EXPECT_FALSE(sp);
}

TEST(TSharedPtr, CopyEmptySharedPointer)
{
    TSharedPtr<TestClass> sp1 = new TestClass();   
    TSharedPtr<TestClass> sp2;

    EXPECT_TRUE(sp1);
    EXPECT_FALSE(sp2);

    sp1 = sp2;

    EXPECT_FALSE(sp1);
    EXPECT_FALSE(sp2);
}