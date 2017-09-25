#include <gtest/gtest.h>
#include "Collections/Dictionary.h"

#include "VString.h"

using namespace Core;

TEST(TDictionary, Insert)
{
    TDictionary<VString, int> dict;

    dict.Insert("Test1", 22);
    dict.Insert("Test2", 44);

    // Pre-emptivly testing accessory here, but we need to :)
    EXPECT_EQ(dict["Test1"], 22);
    EXPECT_EQ(dict["Test2"], 44);
}

TEST(TDictionary, Accessor)
{
    int* ptr = new int;
    *ptr = 22;

    TDictionary<VString, int*> dict;

    dict.Insert("Test1", ptr);

    *ptr = 45;

    // Pre-emptivly testing accessory here, but we need to :)
    EXPECT_EQ(*dict["Test1"], 45);

    delete (ptr);
}

TEST(TDictionary, KeyExists)
{
    TDictionary<VString, int> dict;

    dict.Insert("Test1", 43);

    bool get1 = dict.KeyExists("NonExistent");
    EXPECT_FALSE(get1);

    bool get2 = dict.KeyExists("Test1");
    EXPECT_TRUE(get2);
}

TEST(TDictionary, Get)
{
    TDictionary<VString, int> dict;

    dict.Insert("Test1", 43);

    int val = 0;
    bool get1 = dict.Get("NonExistent", val);
    EXPECT_FALSE(get1);
    EXPECT_EQ(val, 0);

    bool get2 = dict.Get("Test1", val);
    EXPECT_TRUE(get2);
    EXPECT_EQ(val, 43);
}

TEST(TDictionary, Remove)
{
    TDictionary<VString, int> dict;

    dict.Insert("Test1", 43);
    dict.Insert("Test2", 23);
    
    bool removed1 = dict.Remove("NonExistentKey");
    bool removed2 = dict.Remove("Test2");
    bool removed3 = dict.Remove("Test1");

    EXPECT_FALSE(removed1);
    EXPECT_TRUE(removed2);
    EXPECT_TRUE(removed2);
    
    EXPECT_FALSE(dict.KeyExists("Test2"));
    EXPECT_FALSE(dict.KeyExists("Test1"));
}