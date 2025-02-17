#include "../lines.cpp"
#include <gtest/gtest.h>
#include <optional>

TEST(lines_test, pointEq) {
  auto p1 = Point(1, 1);
  auto p2 = Point(1, 1);
  EXPECT_TRUE(p1 == p2);
}

TEST(lines_test, intersection) {
  auto l1 = Line(1, 2, 3);
  auto l2 = Line(2, 4, 6);
  EXPECT_EQ(nullopt, l1.intersection(l2));
}

TEST(lines_test, intersection2) {
  auto l1 = Line(1, 2, 3);
  auto l2 = Line(2, 5, 6);
  EXPECT_NE(nullopt, l1.intersection(l2));
}
