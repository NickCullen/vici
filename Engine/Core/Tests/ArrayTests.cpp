#include "Collections/Array.h"
#include "gtest/gtest.h"

using namespace Core;

TEST(TArray, DefaultConstructor)
{
    TArray<int> arr;

    EXPECT_EQ(arr.GetCount(), 0);
    EXPECT_EQ(arr.GetCapacity(), 10);   // Default capacity is 10
}

TEST(TArray, OverloadedCapacityReserveConstructor)
{
    TArray<int> arr = TArray<int>(25);

    EXPECT_EQ(arr.GetCount(), 0);
    EXPECT_EQ(arr.GetCapacity(), 25);   
}

TEST(TArray, CopyConstructor)
{
    TArray<int> arr1 = TArray<int>(25);
    TArray<int> arr2 = arr1;

    EXPECT_EQ(arr1.GetCount(), 0);
    EXPECT_EQ(arr1.GetCapacity(), 25);   

    EXPECT_EQ(arr1.GetCount(), arr2.GetCount());   
    EXPECT_EQ(arr1.GetCapacity(), arr2.GetCapacity());   
    EXPECT_TRUE(arr1.GetData() != arr2.GetData());
}

TEST(TArray, AddItem)
{
    TArray<int> arr;

    arr.Add(5);

    EXPECT_EQ(arr.GetData()[0], 5); // Not testing [] here
    EXPECT_EQ(arr.GetCount(), 1);

    arr.Add(10);

    EXPECT_EQ(arr.GetData()[1], 10); // Not testing [] here
    EXPECT_EQ(arr.GetCount(), 2);

}

TEST(TArray, AccesorOperator)
{
    TArray<int> arr;
    arr.Add(5);
    arr.Add(10);

    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 10); 
}

TEST(TArray, RemoveOperator)
{
    TArray<char> arr;
    arr.Add('a');
    arr.Add('b');

    arr.Remove(2);  // Out of bounds
    EXPECT_EQ(arr.GetCount(), 2);

    arr.Remove(0);  // First element
    EXPECT_EQ(arr.GetCount(), 1);
    EXPECT_EQ(arr[0], 'b');

    arr.RemoveItem('b');    // Remove by value. 
    EXPECT_EQ(arr.GetCount(), 0);

    // NOTE: there is obviously an issue here when there is 
    // an array of TArray<uint32> types...
}

TEST(TArray, ClearOperator)
{
    TArray<int> arr;
    arr.Add(5);
    arr.Add(10);

    arr.Clear();

    EXPECT_EQ(arr.GetCount(), 0);
    
    // NOTE: there is obviously an issue here when there is 
    // an array of TArray<uint32> types...
}