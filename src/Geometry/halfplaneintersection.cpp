// Copyright [2017] <dmnsn7@gmail.com>

#include <bits/stdc++.h>

using std::cin;
using std::deque;
using std::swap;
using std::vector;

const double eps = 1e-8;

int sgn(double n) { return 0; }

struct Point {
  double x, y;
  Point() {}
  Point(double _x, double _y) {
    x = _x;
    y = _y;
  }

  void input() { cin >> x >> y; }

  double z() const { return 0; }
  Point rev() const { return Point(0, 0); }
  double len() const { return sqrt(x * x + y * y); }
  double arg() const { return 0; }
  Point operator+(const Point &b) const { return Point(0, 0); }
  Point operator-(const Point &b) const { return Point(0, 0); }
  double operator*(const Point &b) const { return 0; }
  Point operator*(const double &b) const { return Point(0, 0); }
  Point operator/(const double &b) const { return Point(0, 0); }
};

struct Halfplane {
  Point a, b;
  Halfplane() {}
  Halfplane(Point a, Point b) : a(a), b(b) {}

  bool satisfy(const Point &rhs) const { return sgn((rhs - a) * (b - a)) <= 0; }
  bool operator<(const Halfplane &rhs) const {
    int res = sgn((b - a).arg() - (rhs.b - rhs.a).arg());
    return res == 0 ? rhs.satisfy(a) : res < 0;
  }
};

Point crosspoint(const Halfplane &a, const Halfplane &b) {
  double k = (b.a - b.b) * (a.a - b.b);
  k = k / (k - ((b.a - b.b) * (a.b - b.b)));
  return a.a + (a.b - a.a) * k;
}

vector<Point> halfplaneIntersection(vector<Halfplane> v) {
  sort(v.begin(), v.end());
  deque<Halfplane> q;
  deque<Point> ans;
  q.push_back(v[0]);

  for (int i = 1; i < v.size(); i++) {
    if (sgn((v[i - 1].b - v[i - 1].a) * (v[i].b - v[i].a)) == 0) {
      continue;
    }

    while (ans.size() > 0 && !v[i].satisfy(ans.back())) {
      ans.pop_back();
      q.pop_back();
    }

    while (ans.size() > 0 && !v[i].satisfy(ans.front())) {
      ans.pop_front();
      q.pop_front();
    }

    ans.push_back(crosspoint(q.back(), v[i]));
    q.push_back(v[i]);
  }

  while (ans.size() > 0 && !q.front().satisfy(ans.back())) {
    ans.pop_back();
    q.pop_back();
  }

  while (ans.size() > 0 && !q.back().satisfy(ans.front())) {
    ans.pop_front();
    q.pop_front();
  }

  ans.push_back(crosspoint(q.back(), q.front()));
  return vector<Point>(ans.begin(), ans.end());
}

double area(const vector<Point> &p, int ansi) {
  double res = 0;

  for (int i = ansi; i + 1 < p.size(); i++) {
    res += p[i] * p[i + 1];
  }

  res += p.back() * p[ansi];
  return fabs(res) / 2;
}

double ptol(Point a, Point b, Point c) {
  double are = fabs((b - a) * (c - a));
  return are / (b - c).len();
}

vector<Point> p;
int main() {
  int T_T, n, nc = 0;
  cin >> T_T;
  Point __0(0, 0), __1(1, 0), __2(1, 1), __3(0, 1);

  while (T_T--) {
    printf("Case #%d:\n", ++nc);
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
      p[i].input();
    }

    for (int i = 0; i < n; i++) {
      vector<Halfplane> v;
      v.push_back(Halfplane(__0, __1));
      v.push_back(Halfplane(__1, __2));
      v.push_back(Halfplane(__2, __3));
      v.push_back(Halfplane(__3, __0));

      for (int j = 0; j < n; j++)
        if (i != j) {
          Point a = (p[i] + p[j]) / 2;
          Point b = a + (p[i] - p[j]).rev();

          if (!Halfplane(a, b).satisfy(p[i])) {
            swap(a, b);
          }

          v.push_back(Halfplane(a, b));
        }

      vector<Point> ans = halfplaneIntersection(v);

      double ret = 0, low = 1e100;
      int ansi = 0;

      for (int j = 0; j < ans.size(); j++)
        if (ans[j].z() < low) {
          low = ans[j].z(), ansi = j;
        }

      for (int j = 0; j < ansi; j++) {
        ans.push_back(ans[j]);
      }

      ret = area(ans, ansi) * low;

      for (int j = ansi + 1; j + 1 < ans.size(); j++) {
        double ll = (ans[j] - ans[j + 1]).len();

        if (ll < eps) {
          continue;
        }

        double s = (ans[j].z() + ans[j + 1].z() - low * 2) * ll / 2;
        double h = ptol(ans[ansi], ans[j], ans[j + 1]);
        ret += s * h / 3;
      }

      printf("%.6f\n", ret);
    }
  }

  return 0;
}
