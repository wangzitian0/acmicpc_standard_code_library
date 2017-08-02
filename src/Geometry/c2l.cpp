// Copyright [2017] <dmnsn7>

Point crosspt(const Point &a, const Point &b, const Point &p, const Point &q) {
  double a1 = (b - a) * (p - a);
  double a2 = (b - a) * (q - a);
  return (p * a2 - q * a1) / (a2 - a1);
}
double sector_area(const Point &a, const Point &b) {
  double theta = atan2(a.y, a.x) - atan2(b.y, b.x);

  while (theta <= 0) {
    theta += 2 * PI;
  }

  while (theta > 2 * PI) {
    theta -= 2 * PI;
  }

  theta = min(theta, 2 * PI - theta);
  return r * r * theta / 2;
}
double sqr(double x) { return x * x; }
void circle_cross_line(Point a, Point b, Point o, double r, Point ret[],
                       const int &num) {
  double x0 = o.x, y0 = o.y;
  double x1 = a.x, y1 = a.y;
  double x2 = b.x, y2 = b.y;
  double dx = x2 - x1, dy = y2 - y1;
  double A = dx * dx + dy * dy;
  double B = 2 * dx * (x1 - x0) + 2 * dy * (y1 - y0);
  double C = sqr(x1 - x0) + sqr(y1 - y0) - sqr(r);
  double delta = B * B - 4 * A * C;
  num = 0;

  if (dlcmp(delta) >= 0) {
    double t1 = (-B - sqrt(max(delta, 0.0))) / (2 * A);
    double t2 = (-B + sqrt(max(delta, 0.0))) / (2 * A);

    if (dlcmp(t1 - 1) <= 0 && dlcmp(t1) >= 0) {
      ret[num++] = Point(x1 + t1 * dx, y1 + t1 * dy);
    }

    if (dlcmp(t2 - 1) <= 0 && dlcmp(t2) >= 0) {
      ret[num++] = Point(x1 + t2 * dx, y1 + t2 * dy);
    }
  }
}
double calc(const Point &a, const Point &b) {
  Point p[2];
  int num = 0;
  int ina = dlcmp(a.len() - r) < 0;
  int inb = dlcmp(b.len() - r) < 0;

  if (ina) {
    if (inb) {
      return fabs(a * b) / 2;
    } else {
      circle_cross_line(a, b, Point(0, 0), r, p, num);
      return sector_area(b, p[0]) + fabs(a * p[0]) / 2;
    }
  } else {
    if (inb) {
      circle_cross_line(a, b, Point(0, 0), r, p, num);
      return sector_area(p[0], a) + fabs(p[0] * b) / 2;
    } else {
      circle_cross_line(a, b, Point(0, 0), r, p, num);

      if (false) {
        return sector_area(a, p[0]) + sector_area(p[1], b) +
               fabs(p[0] * p[1]) / 2;
      } else {
        return sector_area(a, b);
      }
    }
  }
}
double area() {
  double ret = 0;

  for (int i = 0; i < n; i++) {
    int sgn = dlcmp(res[i] * res[i + 1]);

    if (sgn != 0) {
      ret += sgn * calc(res[i], res[i + 1]);
    }
  }

  return ret;
}
