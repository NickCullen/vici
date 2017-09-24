#include "Array.h"
#include "gtest/gtest.h"

using namespace Core;

TEST(TArray, DefaultConstructor)
{
    TArray<int> arr;

    EXPECT_EQ(arr.GetLength(), 0);
    EXPECT_EQ(arr.GetCapacity(), 10);   // Default capacity is 10
}

TEST(TArray, OverloadedCapacityReserveConstructor)
{
    TArray<int> arr = TArray<int>(25);

    EXPECT_EQ(arr.GetLength(), 0);
    EXPECT_EQ(arr.GetCapacity(), 25);   
}

TEST(TArray, CopyConstructor)
{
    TArray<int> arr1 = TArray<int>(25);
    TArray<int> arr2 = arr1;

    EXPECT_EQ(arr1.GetLength(), 0);
    EXPECT_EQ(arr1.GetCapacity(), 25);   

    EXPECT_EQ(arr1.GetLength(), arr2.GetLength());   
    EXPECT_EQ(arr1.GetCapacity(), arr2.GetCapacity());   
    EXPECT_TRUE(arr1.GetData() != arr2.GetData());
}