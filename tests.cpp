#include "vector.h"
#include <gtest/gtest.h>

using namespace BMSTU;


TEST(VectorTests, Constructor) {
    BMSTU::Vector<int> v1(0, 0);
    ASSERT_EQ(v1.GetSize(), 0);
    ASSERT_EQ(v1.GetCapacity(), 0);
    ASSERT_EQ(v1.begin(), nullptr);
    ASSERT_EQ(v1.end(), nullptr);

    BMSTU::Vector<int> v2(5, 0);
    ASSERT_EQ(v2.GetSize(), 5);
    ASSERT_EQ(v2.GetCapacity(), 5);
    ASSERT_NE(v2.begin(), nullptr);

    BMSTU::Vector<int> v3 = {1,2,3,4,5,6};
    ASSERT_EQ(v3.GetSize(), 6);
    ASSERT_EQ(v3.GetCapacity(), 8);
    ASSERT_NE(v3.begin(), nullptr);
}



template<typename Type>
BMSTU::Vector<Type> create() {
    std::cout << "create tmp obj" << std::endl;
    return BMSTU::Vector<int>(5, 1);
}

TEST(VectorTests, MoveTest) {
    BMSTU::Vector<int> v;
    v = create<int>();

    ASSERT_EQ(v.GetSize(), 5);
    ASSERT_EQ(v[0], 1);
}

TEST(VectorTests, CopyTest) {
    auto v1 = BMSTU::Vector(5, 1);
    auto v2 = BMSTU::Vector(v1);
    ASSERT_EQ(v2.GetSize(), 5);
    ASSERT_EQ(v2[0], 1);
}

TEST(VectorTests, SwapTest) {
    BMSTU::Vector<int> v1(0, 0);
    BMSTU::Vector<int> v2(5, 0);

    swap(v1, v2);
    ASSERT_EQ(v1.GetSize(), 5);
}

TEST(VectorTests, Push) {
    BMSTU::Vector<int> v(0, 0);
    ASSERT_EQ(v.GetSize(), 0);
    ASSERT_EQ(v.GetCapacity(), 0);
    ASSERT_EQ(v.begin(), nullptr);

    v.PushBack(1);
    ASSERT_EQ(v.GetSize(), 1);
    ASSERT_EQ(v.GetCapacity(), 1);
    ASSERT_EQ(v[v.GetSize() - 1], 1);

    v.PushBack(2);
    ASSERT_EQ(v.GetSize(), 2);
    ASSERT_EQ(v.GetCapacity(), 2);
    ASSERT_EQ(v[v.GetSize() - 1], 2);

    v.PushBack(5);
    ASSERT_EQ(v.GetSize(), 3);
    ASSERT_EQ(v.GetCapacity(), 4);
    ASSERT_EQ(v[v.GetSize() - 1], 5);

    int x = 7;
    v.PushBack(x);
    ASSERT_EQ(v.GetSize(), 4);
    ASSERT_EQ(v.GetCapacity(), 4);
    ASSERT_EQ(v[v.GetSize() - 1], x);
}

TEST(VectorTests, Pop) {
    BMSTU::Vector<int> v(3, 5);
    ASSERT_EQ(v.GetSize(), 3);
    ASSERT_EQ(v.GetCapacity(), 3);
    ASSERT_NE(v.begin(), nullptr);

    v.PopBack();
    ASSERT_EQ(v.GetSize(), 2);
    ASSERT_EQ(v.GetCapacity(), 3);
    ASSERT_EQ(v[v.GetSize() - 1], 5);
}