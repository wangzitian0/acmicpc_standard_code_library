// Copyright [2017] <dmnsn7@gmail.com>

#include <bits/stdc++.h>

using std::max;
using std::swap;
using std::vector;

const int MAXN = 0;
const int INF = 0;

int ch[MAXN][2], pre[MAXN], key[MAXN];
int add[MAXN], Max[MAXN], rev[MAXN], n;
bool rt[MAXN];
void update_add(int r, int d) {
  if (!r) {
    return;
  }

  key[r] += d;
  add[r] += d;
  Max[r] += d;
}
void update_rev(int r) {
  if (!r) {
    return;
  }

  swap(ch[r][0], ch[r][1]);
  rev[r] ^= 1;
}
void push_down(int r) {
  if (add[r]) {
    update_add(ch[r][0], add[r]);
    update_add(ch[r][1], add[r]);
    add[r] = 0;
  }

  if (rev[r]) {
    update_rev(ch[r][0]);
    update_rev(ch[r][1]);
    rev[r] = 0;
  }
}
void display() {
  for (int i = 1; i <= n; i++) {
    printf("%d %d %d %d <%d>  ", i, ch[i][0], ch[i][1], pre[i], rt[i]);
    printf("%d %d %d\n", add[i], key[i], Max[i]);
  }
}
void push_up(int r) { Max[r] = max(max(Max[ch[r][0]], Max[ch[r][1]]), key[r]); }
void rotate(int x) {
  int y = pre[x], kind = ch[y][1] == x;
  ch[y][kind] = ch[x][!kind];
  pre[ch[y][kind]] = y;
  pre[x] = pre[y];
  pre[y] = x;
  ch[x][!kind] = y;

  if (rt[y]) {
    rt[y] = 0, rt[x] = 1;
  } else {
    ch[pre[x]][ch[pre[x]][1] == y] = x;
  }

  push_up(y);
}
void P(int r) {
  if (!rt[r]) {
    P(pre[r]);
  }

  push_down(r);
}
void splay(int r) {
  P(r);

  while (!rt[r]) {
    int f = pre[r], ff = pre[f];

    if (rt[f]) {
      rotate(r);
    } else if ((ch[ff][1] == f) == (ch[f][1] == r)) {
      rotate(f), rotate(r);
    } else {
      rotate(r), rotate(r);
    }
  }

  push_up(r);
}
int access(int x) {
  int y = 0;

  for (; x; x = pre[y = x]) {
    splay(x);
    rt[ch[x][1]] = 1, rt[ch[x][1] = y] = 0;
    push_up(x);
  }

  return y;
}
bool judge(int u, int v) {
  while (pre[u]) {
    u = pre[u];
  }

  while (pre[v]) {
    v = pre[v];
  }

  return u == v;
}
void mroot(int r) {
  access(r);
  splay(r);
  update_rev(r);
}
void lca(int u, int v) {
  access(v), v = 0;

  while (u) {
    splay(u);

    if (!pre[u]) {
      return;
    }

    rt[ch[u][1]] = 1;
    rt[ch[u][1] = v] = 0;
    push_up(u);
    u = pre[v = u];
  }
}
void link(int u, int v) {
  if (judge(u, v)) {
    puts("-1");
    return;
  }

  mroot(u);
  pre[u] = v;
}
void cut(int u, int v) {
  if (u == v || !judge(u, v)) {
    puts("-1");
    return;
  }

  mroot(u);
  splay(v);
  pre[ch[v][0]] = pre[v];
  pre[v] = 0;
  rt[ch[v][0]] = 1;
  ch[v][0] = 0;
  push_up(v);
}
void ADD(int u, int v, int w) {
  if (!judge(u, v)) {
    puts("-1");
    return;
  }

  lca(u, v);
  update_add(ch[u][1], w);
  update_add(v, w);
  key[u] += w;
  push_up(u);
}
void query(int u, int v) {
  if (!judge(u, v)) {
    puts("-1");
    return;
  }

  lca(u, v);
  printf("%d\n", max(max(Max[v], Max[ch[u][1]]), key[u]));
}
vector<int> G[MAXN];
int que[MAXN];
void bfs() {
  int front = 0, rear = 0;
  que[rear++] = 1;
  pre[1] = 0;

  while (front < rear) {
    int u = que[front++];

    for (int i = 0; i < G[u].size(); i++) {
      int v = G[u][i];

      if (v == pre[u]) {
        continue;
      }

      pre[v] = u;
      que[rear++] = v;
    }
  }
}
int main() {
  int q, u, v;

  while (~scanf("%d", &n)) {
    memset(add, 0, sizeof add);
    memset(pre, 0, sizeof pre);
    memset(rev, 0, sizeof rev);
    memset(ch, 0, sizeof ch);

    for (int i = 0; i <= n; i++) {
      G[i].clear();
      rt[i] = 1;
    }

    Max[0] = -INF;

    for (int i = 1; i < n; i++) {
      scanf("%d%d", &u, &v);
      G[u].push_back(v);
      G[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
      scanf("%d", &key[i]);
      Max[i] = key[i];
    }

    scanf("%d", &q);
    bfs();

    int op, x, y, w;

    while (q--) {
      scanf("%d", &op);

      if (op == 1) {
        scanf("%d%d", &x, &y);
        link(x, y);
      } else if (op == 2) {
        scanf("%d%d", &x, &y);
        cut(x, y);
      } else if (op == 3) {
        scanf("%d%d%d", &w, &x, &y);
        ADD(x, y, w);
      } else {
        scanf("%d%d", &x, &y);
        query(x, y);
      }
    }

    puts("");
  }

  return 0;
}
