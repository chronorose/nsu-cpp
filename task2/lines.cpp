#include "lines.hpp"
#include <concepts>
#include <limits>
#include <optional>

template <std::floating_point fpType>
static bool floatEquality(fpType f1, fpType f2) {

  if (f1 == f2)
    return true;
  auto diff = std::abs(f1 - f2);
  if (diff < std::numeric_limits<fpType>::epsilon()) {
    return true;
  }
  return false;
}

bool Point::operator==(const Point& point) const {
  return floatEquality(point.x, x) && floatEquality(point.y, y);
}

Line::Line(Point& p1, Point& p2) {
  this->A = p1.y - p2.y;
  this->B = p2.x - p1.x;
  this->C = p1.x * p2.y - p2.x * p1.y;
}

std::optional<Line> Line::lineFactory(Point& p1, Point& p2) {
  if (p1 == p2)
    return std::nullopt;

  return Line(p1, p2);
}

std::optional<Line> Line::lineFactory(double A, double B, double C) {
  return Line(A, B, C);
}

/* Note:
 * I love optionals! They are perfectly suits here!
 */
std::optional<Point> Line::intersection(Line& ln2) const {
  double det = this->A * ln2.B - ln2.A * this->B;
  if (floatEquality(det, 0.0)) {
    return {};
  }
  double detdiv = 1. / det;
  double x = detdiv * ((this->B * ln2.C) - (this->C * ln2.B));
  double y = detdiv * ((this->C * ln2.A) - (this->A * ln2.C));
  return Point(x, y);
}

Line Line::perpendicular(Point& p) const {
  int coef = 1;
  if (this->B > 0)
    coef = -1;
  double newA = coef * (-1 * this->B);
  double newB = coef * this->A;
  double newC = coef * (this->B * p.x - this->A * p.y);
  return Line(newA, newB, newC);
}

/* RE: again wrong floating points comparison */
bool Line::operator==(const Line& ln) const {
  return floatEquality(A, ln.A) && floatEquality(B, ln.B) &&
         floatEquality(C, ln.C);
}
