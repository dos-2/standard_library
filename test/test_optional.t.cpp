#include "optional.hpp"
#include <gtest/gtest.h>  // Google Test framework

// Test that fill() correctly sets all elements
TEST(OptionalTest, Default) {
  optional<int> o;
  EXPECT_FALSE(o.has_value());
  EXPECT_FALSE(static_cast<bool>(o));
}

// Test operator[] modification
TEST(OptionalTest, LvalueAndRvalue) {
  int x = 2;
  optional<int> o1(x);
  EXPECT_TRUE(o1.has_value());
  EXPECT_EQ(*o1, 2);

  optional<int>o2(17);
  EXPECT_TRUE(o2.has_value());
  EXPECT_EQ(*o2, 17);
}
