#include <gtest/gtest.h>
#include "WeakPtr.h"

using namespace Core;

class TestClass
{
public:
    int32 TestData = 0;

};

TEST(TWeakPtr, OverloadedSharedPtrConstructor)
{
    TSharedPtr<TestClass> sp = new TestClass();
    sp->TestData = 22;

    TWeakPtr<TestClass> wp = sp;
    EXPECT_EQ(wp->TestData, sp->TestData);

    sp->TestData = 44;
    EXPECT_EQ(wp->TestData, sp->TestData); 

    EXPECT_EQ(sp.GetWeakRefCount(), 1);
}

TEST(TWeakPtr, CopyConstructor)
{
    TSharedPtr<TestClass> sp = new TestClass();
    sp->TestData = 22;

    TWeakPtr<TestClass> wp1 = sp;
    TWeakPtr<TestClass> wp2 = wp1;

    EXPECT_EQ(wp1->TestData, wp2->TestData);

    wp1->TestData = 44;
    EXPECT_EQ(wp1->TestData, wp2->TestData);    
    EXPECT_EQ(wp1->TestData, sp->TestData);

    EXPECT_EQ(sp.GetWeakRefCount(), 2);
}

TEST(TWeakPtr, SharedPointerAssignmentOperator)
{
    TSharedPtr<TestClass> sp = new TestClass();
    sp->TestData = 22;

    TWeakPtr<TestClass> wp1;
    TWeakPtr<TestClass> wp2;

    wp1 = sp;
    wp2 = sp;

    EXPECT_EQ(wp1->TestData, sp->TestData);
    EXPECT_EQ(wp2->TestData, sp->TestData);
    EXPECT_EQ(wp1->TestData, wp2->TestData);
    EXPECT_EQ(sp.GetWeakRefCount(), 2);

    wp1->TestData = 44;
    EXPECT_EQ(wp1->TestData, sp->TestData);
    EXPECT_EQ(wp2->TestData, sp->TestData);
    EXPECT_EQ(wp1->TestData, wp2->TestData);
}

TEST(TWeakPtr, WeakPointerAssignmentOperator)
{
    TSharedPtr<TestClass> sp1 = new TestClass();
    sp1->TestData = 22;

    TSharedPtr<TestClass> sp2 = new TestClass();
    sp2->TestData = 44;

    TWeakPtr<TestClass> wp1 = sp1;
    TWeakPtr<TestClass> wp2 = sp2;

    // Should point to sp2
    wp1 = wp2;

    EXPECT_EQ(wp1->TestData, 44);
    EXPECT_EQ(wp2->TestData, 44);
    EXPECT_EQ(sp1.GetWeakRefCount(), 0);
    EXPECT_EQ(sp2.GetWeakRefCount(), 2);

    //swap to pointer to sp1
    wp2 = sp1;
    wp1 = wp2;

    EXPECT_EQ(wp1->TestData, 22);
    EXPECT_EQ(wp2->TestData, 22);
    EXPECT_EQ(sp1.GetWeakRefCount(), 2);
    EXPECT_EQ(sp2.GetWeakRefCount(), 0);
}

TEST(TWeakPtr, BooleanEvaluation)
{
    TSharedPtr<TestClass> sp = new TestClass();
    sp->TestData = 22;

    TWeakPtr<TestClass> wp1 = sp;
    TWeakPtr<TestClass> wp2;

    EXPECT_TRUE(wp1);
    EXPECT_FALSE(wp2);

    wp2 = sp;
    EXPECT_TRUE(wp2);

}

TEST(TWeakPtr, DereferenceOperator)
{
    TestClass* tc = new TestClass();

    TSharedPtr<TestClass> sp = tc;
    sp->TestData = 22;

    TWeakPtr<TestClass> wp1 = sp;
    TWeakPtr<TestClass> wp2;

    EXPECT_EQ(*wp1, tc);
    EXPECT_EQ(*wp2, nullptr);

    wp2 = sp;
    EXPECT_TRUE(tc);
}


TEST(TWeakPtr, InvalidateByAssignment)
{
    TSharedPtr<TestClass> sp1 = new TestClass();
    sp1->TestData = 22;

    TSharedPtr<TestClass> sp2 = new TestClass();
    sp2->TestData = 44;

    TWeakPtr<TestClass> wp = sp1;

    EXPECT_EQ(sp1.GetWeakRefCount(), 1);
    EXPECT_TRUE(wp);

    // Assign sp2 to sp1, this should destroy
    // original sp1 data and loose weak ref
    sp1 = sp2;

    EXPECT_EQ(sp1.GetWeakRefCount(), 0);
    EXPECT_FALSE(wp);
}

TEST(TWeakPtr, InvalidateByScope)
{
    TWeakPtr<TestClass> wp;
    {
        TSharedPtr<TestClass> sp = new TestClass();

        wp = sp;

        wp->TestData = 22;

        EXPECT_EQ(sp.GetWeakRefCount(), 1);
        EXPECT_TRUE(wp);
        EXPECT_EQ(wp->TestData, sp->TestData);
        EXPECT_EQ(wp->TestData, 22);
    }

    EXPECT_FALSE(wp);
}

TEST(TWeakPtr, ClearByScope)
{
    TSharedPtr<TestClass> sp = new TestClass();   
    {
        TWeakPtr<TestClass> wp = sp;

        EXPECT_EQ(sp.GetWeakRefCount(), 1);
    }
    EXPECT_EQ(sp.GetWeakRefCount(), 0);
}

TEST(TWeakPtr, ClearRefernce)
{
    TSharedPtr<TestClass> sp = new TestClass();   
    TWeakPtr<TestClass> wp = sp;

    EXPECT_EQ(sp.GetWeakRefCount(), 1);
    EXPECT_TRUE(wp);

    wp.ClearReference();

    EXPECT_EQ(sp.GetWeakRefCount(), 0);
    EXPECT_FALSE(wp);
}

TEST(TWeakPtr, CopyEmptyWeakReference)
{
    TSharedPtr<TestClass> sp = new TestClass();   
    TWeakPtr<TestClass> wp1;
    TWeakPtr<TestClass> wp2;

    wp1 = wp2;

    EXPECT_EQ(sp.GetWeakRefCount(), 0);
    EXPECT_FALSE(wp1);
}