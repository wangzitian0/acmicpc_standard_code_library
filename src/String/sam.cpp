// Copyright [2017] <dmnsn7@gmail.com>

#include <bits/stdc++.h>

const int MAXN = 0;

int tot, root, np, tail;
int cnt[MAXN], son[MAXN][MAXN], gao[MAXN], g[MAXN], b[MAXN], len[MAXN],
    pre[MAXN];

void copy(int x, int y) {
  pre[x] = pre[y];
  len[x] = len[y];
  memcpy(son[x], son[y], sizeof son[0]);
}

void insert(int c, int l) {
  int p = tail, np = ++tot;
  len[np] = l;
  tail = np;

  while (p && son[p][c] == 0) {
    son[p][c] = np, p = pre[p];
  }

  if (p == 0) {
    pre[np] = root;
  } else {
    int q = son[p][c];

    if (len[p] + 1 == len[q]) {
      pre[np] = q;
    } else {
      int nq = ++tot;
      copy(nq, q);
      len[nq] = len[p] + 1;
      pre[np] = pre[q] = nq;

      while (p && son[p][c] == q) {
        son[p][c] = nq, p = pre[p];
      }
    }
  }
}

void build(int n) {
  for (int i = 1; i <= tot; i++) {
    cnt[len[i]]++;
  }

  for (int i = 1; i <= n; i++) {
    cnt[i] += cnt[i - 1];
  }

  for (int i = 1; i <= tot; i++) {
    b[--cnt[len[i]]] = i;
  }

  for (int i = tot - 1; i >= 0; i--) {
    int p = b[i], k = 0;
    g[p] = 1;

    for (int j = 0; j < 26; j++)
      if (son[p][j]) {
        int v = son[p][j];
        g[p] += g[v];
        son[p][k] = v;
        gao[v] = j + 'a';
        k++;
      }

    son[p][k] = 0;
  }
}

int main() { return 0; }
