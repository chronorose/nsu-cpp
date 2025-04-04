#include "lines.hpp"
#include <optional>

bool Point::operator==(const Point& point) const {
  return point.x == this->x && point.y == this->y;
}

Line::Line(Point& p1, Point& p2) {
  this->A = p1.y - p2.y;
  this->B = p2.x - p1.x;
  this->C = p1.x * p2.y - p2.x * p1.y;
}

std::optional<Point> Line::intersection(Line& ln2) const {
  double det = this->A * ln2.B - ln2.A * this->B;
  if (det == 0) {
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

bool Line::operator==(const Line& ln) const {
  return this->A == ln.A && this->B == ln.B && this->C == ln.C;
}
