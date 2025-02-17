#include "../treap.hpp"
#include <gtest/gtest.h>
#include <vector>

TEST(treap_tests, test_insert_remove) {
  Treap<int, int> t{};
  t.insert(30, 10);
  auto a = t.remove(10);
  EXPECT_EQ(a, 30);
  a = t.remove(10);
  EXPECT_FALSE(a.has_value());
}

TEST(treap_tests, search_test) {
  Treap<size_t, size_t> t{};
  t.insert(30, 10);
  auto a = t.search(10);
  EXPECT_EQ(a, 30);
  a = t.remove(10);
  EXPECT_TRUE(a.has_value());
}

TEST(treap_tests, sinsert_test) {
  Treap<size_t, size_t> t{};
  t.insert(30, 10);
  t.insert(40, 5);
  auto a = t.search(10);
  EXPECT_EQ(a, 30);
  a = t.remove(10);
  EXPECT_TRUE(a.has_value());
}
