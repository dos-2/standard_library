#include "shared_ptr.hpp"
#include <cmath>
#include <gtest/gtest.h>  // Google Test framework
#include <stdexcept>

// Test that fill() correctly sets all elements
TEST(SharedPtrTest, Default) {
  shared_ptr<int> sp;
  EXPECT_FALSE(sp);
  EXPECT_EQ(sp.use_count(), 0);
}


TEST(SharedPtrTest, ConstructorFromPointer) {
  shared_ptr<int> sp(new int(20));
  EXPECT_TRUE(sp);
  EXPECT_EQ(sp.use_count(), 1);
  EXPECT_EQ(*sp, 20);
}

TEST(SharedPtrTest, CopyConstructorIncrementsRefCount) {
  shared_ptr<int> sp1(new int(100));
  shared_ptr<int> sp2(sp1);
  EXPECT_EQ(sp1.use_count(), 2);
  EXPECT_EQ(sp2.use_count(), 2);
  EXPECT_EQ(*sp1, 100);
  EXPECT_EQ(*sp2, 100);
}

TEST(SharedPtrTest, MoveConstructorTransfersOwnership) {
  shared_ptr<int> sp1(new int(100));
  shared_ptr<int> sp2(std::move(sp1));
  EXPECT_FALSE(sp1);
  EXPECT_EQ(sp2.use_count(), 1);
  EXPECT_EQ(*sp2, 100);
}

TEST(SharedPtrTest, DereferenceThrowsOnNull) {
  shared_ptr<int> sp;
  EXPECT_THROW(*sp, std::runtime_error);
}

TEST(SharedPtrTest, ResetWithoutArg) {
  shared_ptr<int> sp(new int(10));
  EXPECT_TRUE(sp);
  EXPECT_EQ(sp.use_count(), 1);

  sp.reset();

  EXPECT_FALSE(sp);
  EXPECT_EQ(sp.use_count(), 0);
}
