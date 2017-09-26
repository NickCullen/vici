#include <gtest/gtest.h>
#include "Collections/Queue.h"

using namespace Core;

TEST(TQueue, DefaultConstructor)
{
    TQueue<int> q;

    EXPECT_EQ(q.GetCount(), 0);
}

TEST(TQueue, Add)
{
    TQueue<int> q;

    q.Add(10);
    q.Add(20);
    q.Add(30);

    EXPECT_EQ(q.GetCount(), 3);
}

TEST(TQueue, Get)
{
    TQueue<int> q;

    q.Add(10);
    q.Add(20);
    q.Add(30);

    int v1 = 0, v2 = 0, v3 = 0, v4 = 0;

    bool r1 = q.Get(v1);
    bool r2 = q.Get(v2);
    bool r3 = q.Get(v3);
    bool r4 = q.Get(v4);

    EXPECT_EQ(q.GetCount(), 0);

    EXPECT_TRUE(r1);
    EXPECT_TRUE(r2);
    EXPECT_TRUE(r3);
    EXPECT_FALSE(r4);

    EXPECT_EQ(v1, 10);
    EXPECT_EQ(v2, 20);
    EXPECT_EQ(v3, 30);
    EXPECT_EQ(v4, 0);
}

TEST(TQueue, Clear)
{
    TQueue<int> q;

    q.Add(10);
    q.Add(20);
    q.Add(30);

    EXPECT_EQ(q.GetCount(), 3);

    q.Clear();

    EXPECT_EQ(q.GetCount(), 0);

    int val = 0;
    bool ret = q.Get(val);

    EXPECT_FALSE(ret);
    EXPECT_EQ(val, 0);
}