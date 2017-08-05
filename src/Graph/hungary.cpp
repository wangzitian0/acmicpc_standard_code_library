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
