#include "../lines.hpp"
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
