// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include "shared_ptr.hpp"

class TestClass{
public:
    int a;
};

TEST(SharedPtr, DefaultTest) {
    SharedPtr<int> a;
    EXPECT_EQ(a.get(), nullptr);
}
TEST(SharedPtr, ExplicitTest){
    SharedPtr<int> a(new int (3228));
    EXPECT_EQ(*a, 3228);
}
TEST(SharedPtr, CopyTest){
    SharedPtr<int> a(new int (3228));
    SharedPtr<int> b(a);
    SharedPtr<int> c;
    c = b;
    EXPECT_EQ(*a, 3228);
    EXPECT_EQ(b.use_count(), 3);
}
TEST(SharedPtr, MoveTest){
    SharedPtr<int> a(new int(3228));
    SharedPtr<int> b(move(a));
    SharedPtr<int> c;
    c=move(b);
    EXPECT_EQ(*c, 3228);
}
TEST(SharedPtr, BoolTest){
    SharedPtr<int> a(new int(3228));
    SharedPtr<int> b = a;
    bool result = (bool)b;
    EXPECT_TRUE(result);
}
TEST(SharedPtr, ArrowTest){
    auto testPointer = new TestClass;
    testPointer -> a = 3228;
    SharedPtr<TestClass> pointer(testPointer);
    EXPECT_EQ(pointer->a,testPointer->a);
}
TEST(SharedPtr, ResetTest){
    SharedPtr<int> a(new int(3228));
    a.reset();
    EXPECT_EQ(a.get(), nullptr);
}
TEST(SharedPtr, ResetPointerTest){
    int* a = new int(3228);
    int* b = new int(8223);
    SharedPtr<int> pointer(a);
    pointer.reset(b);
    EXPECT_EQ(pointer.get(), b);
}
TEST(SharedPtr, SwapTest){
    SharedPtr<int> a(new int(3228));
    SharedPtr<int> b(new int(8223));
    a.swap(b);
    EXPECT_EQ(*a,8223);
    EXPECT_EQ(*b, 3228);
}
TEST(SharedPtr, IsMoveTest){
    EXPECT_EQ(std::is_move_assignable<SharedPtr<int>>::value, true);
    EXPECT_EQ(std::is_move_constructible<SharedPtr<int>>::value, true);
    EXPECT_EQ(std::is_move_assignable<SharedPtr<double>>::value, true);
    EXPECT_EQ(std::is_move_constructible<SharedPtr<double>>::value, true);
    EXPECT_EQ(std::is_move_assignable<SharedPtr<TestClass>>::value, true);
    EXPECT_EQ(std::is_move_constructible<SharedPtr<TestClass>>::value, true);
}
TEST(SharedPtr, IsCopyTest){
    EXPECT_EQ(std::is_copy_assignable<SharedPtr<int>>::value, true);
    EXPECT_EQ(std::is_copy_constructible<SharedPtr<int>>::value, true);
    EXPECT_EQ(std::is_copy_assignable<SharedPtr<double>>::value, true);
    EXPECT_EQ(std::is_copy_constructible<SharedPtr<double>>::value, true);
    EXPECT_EQ(std::is_copy_assignable<SharedPtr<TestClass>>::value, true);
    EXPECT_EQ(std::is_copy_constructible<SharedPtr<TestClass>>::value, true);
}
