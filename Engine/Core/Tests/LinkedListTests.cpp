#include <gtest/gtest.h>
#include "Collections/LinkedList.h"

using namespace Core;


TEST(TLinkedList, Add)
{
    TLinkedList<int> lst;

    lst.Add(25);
    lst.Add(50);

    // Premptive testing here, but needed..
    int total = 0;
    for(auto i : lst)
    {
        total += i;
    }

    EXPECT_EQ(total, 75);
}

TEST(TLinkedList, Iterate)
{
    TLinkedList<int> lst1;

    lst1.Add(25);
    lst1.Add(50);

    // Premptive testing here, but needed..
    int total = 0;
    for(auto i : lst1)
    {
        total += i;
    }

    EXPECT_EQ(total, 75);

    TLinkedList<int> lst2;
    
    total = 0;
    for(auto i : lst2)
    {
        total += i;
    }
    
    EXPECT_EQ(total, 0);
}

TEST(TLinkedList, Clear)
{
    TLinkedList<int> lst;

    lst.Add(25);
    lst.Add(50);
    
    lst.Clear();

    int total = 0;
    for(auto i : lst)
    {
        total += i;
    }
    
    EXPECT_EQ(total, 0);
}

TEST(TLinkedList, Remove)
{
    TLinkedList<int> lst;

    lst.Add(25);
    lst.Add(50);
    
    bool removed1 = lst.Remove(25);
    bool removed2 = lst.Remove(33);
    
    EXPECT_TRUE(removed1);
    EXPECT_FALSE(removed2);
    
    int total = 0;
    for(auto i : lst)
    {
        total += i;
    }
    
    EXPECT_EQ(total, 50);
}
