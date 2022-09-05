#include <gtest/gtest.h>
#include "hash_for_luxoft.h"

TEST(addAndFindTest, HashForLuxoftTest) {
  HashForLuxoft<int> h;
  ASSERT_NO_THROW(h.add(1));
  ASSERT_TRUE(h.find(1));
  ASSERT_NO_THROW(h.add(2));
  ASSERT_TRUE(h.find(2));
  ASSERT_NO_THROW(h.add(3));
  ASSERT_TRUE(h.find(3));
  ASSERT_NO_THROW(h.add(-1));
  ASSERT_TRUE(h.find(-1));

  ASSERT_FALSE(h.find(0));
}

TEST(addAndRemoveTest, HashForLuxoftTest) {
  HashForLuxoft<int> h;
  ASSERT_NO_THROW(h.add(1));
  ASSERT_TRUE(h.find(1));
  ASSERT_NO_THROW(h.remove(1));
  ASSERT_FALSE(h.find(1));
}


