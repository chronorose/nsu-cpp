#pragma once

#include <optional>

struct Point {
  double x;
  double y;
  Point(double x, double y) : x(x), y(y) {}

  bool operator==(const Point& point) const;
};

class Line {
public:
  double A;
  double B;
  double C;

  Line(Point& p1, Point& p2);

  Line(double A, double B, double C) : A(A), B(B), C(C) {}

  std::optional<Point> intersection(Line& ln2) const;

  Line perpendicular(Point& p) const;

  bool operator==(const Line& ln) const;
};
