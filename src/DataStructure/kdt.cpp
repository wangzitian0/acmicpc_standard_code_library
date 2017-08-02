// Copyright [2017] <dmnsn7>

bool cmpx(const Node &a, const Node &b) { return a.x < b.x; }
bool cmpy(const Node &a, const Node &b) { return a.y < b.y; }

LL dis(const Node &a, const Node &b) { return sqr(a.x - b.x) + sqr(a.y - b.y); }

void build(int l, int r) {
  if (l > r) {
    return;
  }

  LL minx = min_element(p + l, p + r + 1, cmpx)->x;
  LL maxx = max_element(p + l, p + r + 1, cmpx)->x;
  LL miny = min_element(p + l, p + r + 1, cmpy)->y;
  LL maxy = max_element(p + l, p + r + 1, cmpy)->y;
  int mid = l + (r - l) / 2;
  d[mid] = maxx - minx > maxy - miny;
  nth_element(p + l, p + mid, p + r + 1, d[mid] ? cmpx : cmpy);

  build(l, mid - 1);
  build(mid + 1, r);
}

void query(int l, int r, const Node &a) {
  if (l > r) {
    return;
  }

  int mid = l + (r - l) / 2;
  LL dist = dis(a, p[mid]);
  LL d1 = d[mid] ? a.x - p[mid].x : a.y - p[mid].y;

  if (dist > 0) {
    res = min(res, dist);
  }

  int l1 = l, r1 = mid - 1;
  int l2 = mid + 1, r2 = r;

  if (d1 > 0) {
    swap(l1, l2);
    swap(r1, r2);
  }

  query(l1, r1, a);

  if (d1 * d1 < res) {
    query(l2, r2, a);
  }
}
