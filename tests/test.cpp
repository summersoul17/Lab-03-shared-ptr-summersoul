// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include "shared_ptr.hpp"

TEST(SharedPtr, DefaultTest) {
    SharedPtr<int> a;
}
TEST(SharedPtr, ExplicitTest){
    SharedPtr<int> a(new int (3228));
}
TEST(SharedPtr, CopyTest){
    SharedPtr<int> a(new int (3228));
    SharedPtr<int> b(a);
    SharedPtr<int> c;
    c = b;
}
TEST(SharedPtr, MoveTest){
    SharedPtr<int> a(new int(3228));
    SharedPtr<int> b(move(a));
    SharedPtr<int> c;
    c=move(b);
}
TEST(SharedPtr, BoolTest){
    SharedPtr<int> a(new int(3228));
    SharedPtr<int> b = a;
    bool result = b;
}
TEST(SharedPtr, RefTest){

}
TEST(SharedPtr, ArrowTest){

}
TEST(SharedPtr, GetTest){

}
TEST(SharedPtr, ResetTest){

}
TEST(SharedPtr, SwapTest){

}
TEST(SharedPtr, Use_countTest){

}
