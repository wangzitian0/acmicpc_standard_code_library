// Copyright [2017] <dmnsn7>

Point rotate(const Point &p, double cost, double sint) {
  double x = p.x, y = p.y;
  return Point(x * cost - y * sint, x * sint + y * cost);
}

void circle_cross_circle(Circle a, Circle b, Point cro[]) {
  double d = (a.o - b.o).len();
  double cost = (a.r * a.r + d * d - b.r * b.r) / (2 * a.r * d);
  double sint = sqrt(max(1.0 - cost * cost, 0.0));
  Point v = (b.o - a.o) * (a.r / d);
  cro[0] = a.o + rotate(v, cost, -sint);
  cro[1] = a.o + rotate(v, cost, sint);
}
