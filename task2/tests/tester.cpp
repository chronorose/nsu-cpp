#include "../lines.hpp"
#include <cmath>
#include <gtest/gtest.h>

TEST(lines_test, intersection_test) {
  double a, b, c;
  const int amount = 20;
  a = 1;
  b = 2;
  c = 3;
  auto lineOpt = Line::lineFactory(a, b, c);
  ASSERT_TRUE(lineOpt.has_value());
  auto line = *lineOpt;
  for (int i = -amount; i < amount; i++) {
    auto newLineOpt = Line::lineFactory(a * i, b * i, c * i);
    ASSERT_TRUE(newLineOpt.has_value());
    auto newLine = *newLineOpt;
    auto point = line.intersection(newLine);
    EXPECT_EQ(point, std::nullopt);
  }
}

TEST(lines_test, perpendicular) {
  auto lineOpt = Line::lineFactory(1, 2, 3);
  ASSERT_TRUE(lineOpt.has_value());
  auto line = *lineOpt;
  auto lineExpectedOpt = Line::lineFactory(2, -1, 0);
  ASSERT_TRUE(lineExpectedOpt.has_value());
  auto lineExpected = *lineExpectedOpt;
  Point p{1, 2};
  EXPECT_EQ(line.perpendicular(p), lineExpected);
}

TEST(lines_test, perpendicular2) {
  auto lineOpt = Line::lineFactory(1, 2, 3);
  ASSERT_TRUE(lineOpt.has_value());
  auto line = *lineOpt;
  auto lineExpectedOpt = Line::lineFactory(2, -1, -2);
  ASSERT_TRUE(lineExpectedOpt.has_value());
  auto lineExpected = *lineExpectedOpt;
  Point p{2, 2};
  EXPECT_EQ(line.perpendicular(p), lineExpected);
}

TEST(lines_test, perpendicular3) {
  auto lineOpt = Line::lineFactory(1.5, 2.5, 3.5);
  ASSERT_TRUE(lineOpt.has_value());
  auto line = *lineOpt;
  auto lineExpectedOpt = Line::lineFactory(2.5, -1.5, -11.5);
  ASSERT_TRUE(lineExpectedOpt.has_value());
  auto lineExpected = *lineExpectedOpt;
  Point p{11.5, 11.5};
  EXPECT_EQ(line.perpendicular(p), lineExpected);
}

TEST(review_test, broken_invariants) {
  Point p1{1, 1};
  Point p2{1, 1};

  auto lineOpt = Line::lineFactory(p1, p2);
  ASSERT_FALSE(lineOpt.has_value());
}

TEST(review_test, tricky_floats) {

  // You can check that these lines are parrallel

  auto lineOpt = Line::lineFactory(1.0 / 3, 2, 0);
  ASSERT_TRUE(lineOpt.has_value());
  auto line = *lineOpt;
  auto lineExpectedOpt = Line::lineFactory(0.1, 3.0 / 5, 1);
  ASSERT_TRUE(lineExpectedOpt.has_value());
  auto lineExpected = *lineExpectedOpt;

  auto intersection = line.intersection(lineExpected);

  // So there is not intersection, right?
  ASSERT_FALSE(intersection.has_value());
}
