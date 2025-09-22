#include "array.hpp"
#include <gtest/gtest.h>  // Google Test framework

// Test that fill() correctly sets all elements
TEST(ArrayTest, Fill) {
    array<int, 5> arr;
    arr.fill(42);

    for (size_t i = 0; i < arr.size(); ++i) {
        EXPECT_EQ(arr[i], 42);
    }
}

// Test operator[] modification
TEST(ArrayTest, OperatorIndex) {
    array<int, 3> arr;
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, SizeTest) {
    array<double, 4> arr;
    EXPECT_EQ(arr.size(), 4);
}
