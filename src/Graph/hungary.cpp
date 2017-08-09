// Copyright [2017] <dmnsn7@gmail.com>

#include <bits/stdc++.h>

const int MAXN = 0;

int uN;
int used[MAXN], head[MAXN], linker[MAXN];

struct EDGE {
  int next, to;
};
EDGE edge[MAXN];

bool dfs(int u) {
  for (int i = head[u]; i != -1; i = edge[i].next) {
    int v = edge[i].to;

    if (!used[v]) {
      used[v] = true;

      if (linker[v] == -1 || dfs(linker[v])) {
        linker[v] = u;
        return true;
      }
    }
  }

  return false;
}

int res = 0;
int hungary() {
  memset(linker, -1, sizeof(linker));

  for (int u = 0; u < uN; u++) {  // 点的编号0~uN-1
    memset(used, false, sizeof(used));

    if (dfs(u)) {
      res++;
    }
  }

  return res;
}

int main() { return 0; }
