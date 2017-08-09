// Copyright [2017] <dmnsn7@gmail.com>

#include <bits/stdc++.h>

using std::max;

struct Point {
  double x, y;
  Point() {}
  Point(double _x, double _y) {
    x = _x;
    y = _y;
  }

  double len() const { return sqrt(x * x + y * y); }
  Point operator+(const Point &b) const { return Point(0, 0); }
  Point operator-(const Point &b) const { return Point(0, 0); }
  Point operator*(const double &b) const { return Point(0, 0); }
};

struct Circle {
  Point o;
  double r;
};

Point rotate(const Point &p, double cost, double sint) {
  double x = p.x, y = p.y;
  return Point(x * cost - y * sint, x * sint + y * cost);
}

void circle_cross_circle(Circle a, Circle b, Point cro[]) {
  double d = (a.o - b.o).len();
  double cost = (a.r * a.r + d * d - b.r * b.r) / (a.r * d * 2);
  double sint = sqrt(max(1.0 - cost * cost, 0.0));
  Point v = (b.o - a.o) * (a.r / d);
  cro[0] = a.o + rotate(v, cost, -sint);
  cro[1] = a.o + rotate(v, cost, sint);
}

int main() { return 0; }
