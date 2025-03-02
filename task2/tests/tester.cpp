#include "../lines.hpp"
#include <cmath>
#include <gtest/gtest.h>

TEST(lines_test, intersection_test) {
  double a, b, c;
  const int amount = 20;
  a = 1;
  b = 2;
  c = 3;
  Line line = Line(a, b, c);
  for (int i = -amount; i < amount; i++) {
    Line new_line = Line(a * i, b * i, c * i);
    auto point = line.intersection(new_line);
    EXPECT_EQ(point, std::nullopt);
  }
}

TEST(lines_test, perpendicular) {
  Line line{1, 2, 3};
  Line lineExpected{2, -1, 0};
  Point p{1, 2};
  EXPECT_EQ(line.perpendicular(p), lineExpected);
}

TEST(lines_test, perpendicular2) {
  Line line{1, 2, 3};
  Line lineExpected{2, -1, -2};
  Point p{2, 2};
  EXPECT_EQ(line.perpendicular(p), lineExpected);
}

TEST(lines_test, perpendicular3) {
  Line line{1.5, 2.5, 3.5};
  Line lineExpected{2.5, -1.5, -11.5};
  Point p{11.5, 11.5};
  EXPECT_EQ(line.perpendicular(p), lineExpected);
}

TEST(review_test, broken_invariants) {
    Point p1 {1, 1};
    Point p2 {1, 1};

    Line l {p1, p2};

    // line trough the same points is weird
    // in your case it will be whole plain)
    ASSERT_TRUE(std::fabs(l.A) + std::fabs(l.B) + std::fabs(l.C) != 0.0);
}

TEST(review_test, tricky_floats) {

  // You can check that these lines are parrallel
  Line first(1.0 / 3, 2, 0);
  Line second(0.1, 3.0 / 5, 1);

  auto intersection = first.intersection(second);
  
  // So there is not intersection, right?
  ASSERT_FALSE(intersection.has_value());
}
