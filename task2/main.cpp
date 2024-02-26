#include <iostream>
#include <optional>

using namespace std;

#define IS_TRUE(x) { if (!(x)) cout << "function: " <<  __FUNCTION__ << " failed on line " << __LINE__ << endl; }

struct Point {
    double x;
    double y;
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
    bool operator==(Point point) {
        if(point.x == this->x && point.y == this->y) {
            return true;
        }
        return false;
    }
};

ostream& operator<<(ostream& os, Point& p) {
    os << p.x << " " << p.y << endl;
    return os;
}

class Line {
    double A;
    double B;
    double C;
    public:
    friend ostream& operator<<(ostream& os, Line& ln);
    Line(Point& p1, Point& p2) {
        this->A = p1.y - p2.y;
        this->B = p2.x - p1.x;
        this->C = p1.x * p2.y - p2.x * p1.y;
    }
    Line(int A, int B, int C) {
        this->A = A;
        this->B = B;
        this->C = C;
    }
    optional<Point> intersection(Line& ln2) const {
        double det = this->A * ln2.B - ln2.A * this->B;
        if (det == 0) {
            return {};
        } else {
            double detdiv = 1. / det;
            double x = detdiv * ((this->B * ln2.C) - (this->C * ln2.B));
            double y = detdiv * ((this->C * ln2.A) - (this->A * ln2.C));
            return Point(x, y);
        }

    }
    Line perpendicular(Point& p) const {
        int coef = 1;
        if (this->B > 0)
            coef = -1;
        double newA = coef * (-1 * this->B);
        double newB = coef * this->A;
        double newC = coef * (this->B * p.x - this->A * p.y);
        Line ln(newA, newB, newC);
        return ln;
    }
    bool operator==(Line ln) {
        if (this->A == ln.A && this->B == ln.B && this->C == ln.C) {
            return true;
        }
        return false;
    }
};

ostream& operator<<(ostream& os, Line& ln) {
    cout << ln.A << " " << ln.B << " " << ln.C << endl;    
    return os;
}

Line fastPerpendTest(double A, double B, double C, double x, double y) {
    Line ln(A, B, C);
    Point p(x, y);
    return ln.perpendicular(p);
}

optional<Point> fastIntersectTest(double A1, double B1, double C1, 
                                  double A2, double B2, double C2) {
    Line ln1(A1, B1, C1);
    Line ln2(A2, B2, C2);
    return ln1.intersection(ln2);
}

void tests() {
    IS_TRUE(fastPerpendTest(2, -1, 5, 4, -3) == Line(1, 2, 2));
    IS_TRUE(fastPerpendTest(1, 2, 3, 1, 2) == Line(2, -1, 0));
    IS_TRUE(fastPerpendTest(1, 4, 3, 1, 2) == Line(4, -1, -2));
    IS_TRUE(fastPerpendTest(1, 4, 300, 1, 2) == Line(4, -1, -2));
    IS_TRUE(*fastIntersectTest(1, 2, 3, 4, 5, 6) == Point(1, -2));
    IS_TRUE(*fastIntersectTest(1, 2, 3, 4, 5, 6) == Point(1, -2));
    IS_TRUE(*fastIntersectTest(1, 2, 3, 4, 5, 6) == Point(1, -2));
    IS_TRUE(*fastIntersectTest(1, 1, 2, 5, 6, 7) == Point(-5, 3));
}


int main() {
    tests();
    return 0;
}
