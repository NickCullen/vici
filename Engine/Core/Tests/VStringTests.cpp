#include "VString.h"
#include "gtest/gtest.h"

using namespace Core;

TEST(VString, DefaultConstructor) {
    VString str;

    EXPECT_EQ(0, str.GetLength());
    EXPECT_EQ(0, str.GetCapacity());
    EXPECT_TRUE(str.GetData() == nullptr);
}

TEST(VString, ConstCharConstructor) {
    VString str("Hello");

    EXPECT_STREQ(str.GetData(), "Hello");
    EXPECT_EQ(str.GetLength(), 5);
}

TEST(VString, CopyConstructor) {
    VString str1("Hello");
    VString str2(str1);

    EXPECT_STREQ(str1.GetData(), str2.GetData());
    EXPECT_EQ(str1.GetLength(), str2.GetLength());
    EXPECT_EQ(str1.GetCapacity(), str2.GetCapacity());
}

TEST(VString, EqualityConditionConstChar) {
    VString str("Hello");

    EXPECT_TRUE(str == "Hello");
    EXPECT_FALSE(str == "Bye");
}

TEST(VString, EqualityCondition) {
    VString str1("Hello");
    VString str2("Bye");
    VString str3("Hello");

    EXPECT_TRUE(str1 == str3);
    EXPECT_FALSE(str1 == str2);
}

TEST(VString, AssignmentOperatorConstChar) {
    VString str;
    str = "Hello";

    EXPECT_STREQ(str.GetData(), "Hello");
    EXPECT_EQ(str.GetLength(), 5);
}

TEST(VString, AssignmentOperatorCondition) {
    VString str1("Hello");
    VString str2("Bye");

    str1 = str2;

    EXPECT_STREQ(str1.GetData(), str2.GetData());
    EXPECT_EQ(str1.GetLength(), str2.GetLength());
    EXPECT_EQ(str1.GetCapacity(), str2.GetCapacity());
}

TEST(VString, InequalityConditionConstChar) {
    VString str("Hello");

    EXPECT_TRUE(str != "Bye");
    EXPECT_FALSE(str != "Hello");
}

TEST(VString, InequalityCondition) {
    VString str1("Hello");
    VString str2("Bye");
    VString str3("Hello");

    EXPECT_TRUE(str1 != str2);
    EXPECT_FALSE(str1 != str3);
}

TEST(VString, AddOperatorConstChar) {
    VString str = "1";
    str = str + "2";

    EXPECT_TRUE(str == "12");
    EXPECT_EQ(str.GetLength(), 2);
}

TEST(VString, AddOperator) {
    VString str1 = "1";
    VString str2 = "2";
    VString str3 = str1 + str2;

    EXPECT_TRUE(str3 == "12");
    EXPECT_EQ(str3.GetLength(), 2);
}

TEST(VString, FirstIndexOfConstChar) {
    VString str = "Hello";

    uint32 idx = str.FirstIndexOf("l");
    EXPECT_EQ(idx, 2);

    idx = str.FirstIndexOf("j");
    EXPECT_EQ(idx, VString::INVALID_POS);
}

TEST(VString, FirstIndexOf) {
    VString str = "Hello";

    VString lStr = "l";
    VString jStr = "j";

    uint32 idx = str.FirstIndexOf(lStr);
    EXPECT_EQ(idx, 2);

    idx = str.FirstIndexOf(jStr);
    EXPECT_EQ(idx, VString::INVALID_POS);
}

TEST(VString, LastIndexOfConstChar) {
    VString str = "Hello";

    uint32 idx = str.LastIndexOf("l");
    EXPECT_EQ(idx, 3);

    idx = str.LastIndexOf("j");
    EXPECT_EQ(idx, VString::INVALID_POS);
}


TEST(VString, LastIndexOf) {
    VString str = "Hello";

    VString lStr = "l";
    VString jStr = "j";

    uint32 idx = str.LastIndexOf(lStr);
    EXPECT_EQ(idx, 3);

    idx = str.LastIndexOf(jStr);
    EXPECT_EQ(idx, VString::INVALID_POS);
}

TEST(VString, GetSubstr) {
    const char* sentence = "Hello, world from Vici";

    VString str = sentence;

    VString str1 = str.GetSubstr(0, 5);
    VString str2 = str.GetSubstr(7, 5);
    VString str3 = str.GetSubstr(str.GetLength() - 3, 10);  // Overshoot

    EXPECT_STREQ(str1.GetData(), "Hello");
    EXPECT_STREQ(str2.GetData(), "world");
    EXPECT_STREQ(str3.GetData(), "ici");
    EXPECT_STREQ(str.GetData(), sentence);

    EXPECT_EQ(str1.GetLength(), 5);
    EXPECT_EQ(str2.GetLength(), 5);
    EXPECT_EQ(str3.GetLength(), 3);
}
