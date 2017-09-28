#include <gtest/gtest.h>

template<int I>
struct Evaluator;

#define EVAL(t) Evaluator<t::Value>()

template<typename T>
struct StarCounter
{
    static const int Value = 0;
};

template<typename T>
struct StarCounter<T*>
{
    static const int Value = 1 + StarCounter<T>::Value;
};

TEST(TMP, StarCounter)
{
    int c1 = StarCounter<int>::Value;
    int c2 = StarCounter<int*>::Value;
    int c3 = StarCounter<int****>::Value;

    EXPECT_EQ(c1, 0);
    EXPECT_EQ(c2, 1);
    EXPECT_EQ(c3, 4);
}

template<int I>
struct Factorial
{
    static const int Value = I * Factorial<I - 1>::Value;
};

template<>
struct Factorial<1>
{
    static const int Value = 1;
};

TEST(TMP, Factorial)
{
    int c1 = Factorial<5>::Value;

    EXPECT_EQ(c1, 120);
}

struct Null {};

template<int Value_, typename Next_>
struct Node
{
    static const int Value = Value_;
    typedef Next_ Next;
};

template<typename List>
struct Sum
{
    static const int Value = List::Value + Sum<typename List::Next>::Value;
};

template<>
struct Sum<Null>
{
    static const int Value = 0;
};

TEST(TMP, List)
{
    int total = Sum<Node<5, Node<4, Node<3, Node<2, Node<1, Null>>>>>>::Value;
    EXPECT_EQ(15, total);
}


struct Var
{ 
    static const int Value = 22;
};

struct Type
{ 
    typedef int Value;
};

template<typename T>
int FunVar()
{
    return T::Value;
}

template<typename T>
typename T::Value FunType()
{
    typename T::Value localVar = 30;
    return localVar;
}

TEST(TMP, TypeNameVsVar)
{
    int i1 = FunVar<Var>();
    int i2 = FunType<Type>();

    EXPECT_EQ(i1, 22);
    EXPECT_EQ(i2, 30);
}