#include <gtest/gtest.h>
#include "Collections/Stack.h"

using namespace Core;

TEST(TStack, DefaultConstructor)
{
    TStack<int> stack;

    EXPECT_EQ(stack.GetCount(), 0);
}

TEST(TStack, Push)
{
    TStack<int> stack;

    stack.Push(10);
    stack.Push(20);
    stack.Push(30);

    EXPECT_EQ(stack.GetCount(), 3);
}

TEST(TStack, Peek)
{
    TStack<int> stack;
    
    int v1 = 0;
    bool r1 = stack.Peek(v1);

    stack.Push(10);
    stack.Push(20);
    stack.Push(30);

    int v2 = 0;
    bool r2 = stack.Peek(v2);

    EXPECT_FALSE(r1);
    EXPECT_TRUE(r2);

    EXPECT_EQ(v1, 0);
    EXPECT_EQ(v2, 30);

    EXPECT_EQ(stack.GetCount(), 3);
}


TEST(TStack, Pop)
{
    TStack<int> stack;
    
    int v1 = 0;
    bool r1 = stack.Pop(v1);

    stack.Push(10);

    int v2 = 0;
    bool r2 = stack.Pop(v2);

    // Pop until passed empty
    int v3 = 0;
    bool r3 = stack.Pop(v3);

    EXPECT_FALSE(r1);
    EXPECT_TRUE(r2);
    EXPECT_FALSE(r3);

    EXPECT_EQ(v1, 0);
    EXPECT_EQ(v2, 10);
    EXPECT_EQ(v3, 0);

    EXPECT_EQ(stack.GetCount(), 0);
}

TEST(TStack, Clear)
{
    TStack<int> stack;
    
    stack.Push(10);
    stack.Push(20);
    stack.Push(30);
    
    stack.Clear();

    // Pop until passed empty
    int v = 0;
    bool r = stack.Pop(v);

    EXPECT_FALSE(r);

    EXPECT_EQ(v, 0);

    EXPECT_EQ(stack.GetCount(), 0);
}