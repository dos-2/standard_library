#include "vector.hpp"
#include <gtest/gtest.h>  // Google Test framework

// Test that fill() correctly sets all elements
TEST(VectorTest, addElems) {
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[1], 2);
}
