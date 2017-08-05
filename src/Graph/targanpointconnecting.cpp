void Tarjan(int u, int pre) {
  Low[u] = DFN[u] = ++Index;
  Stack[top++] = u;
  Instack[u] = true;

  for (int i = head[u]; i != -1; i = edge[i].next) {
    int v = edge[i].to;

    if (v == pre) {
      continue;  //无向图
    }

    if (!DFN[v]) {
      Tarjan(v, u);

      if (Low[u] > Low[v]) {
        Low[u] = Low[v];
      }
      /*
      if (Low[v] >= DFN[u]) {
        block++;
        int vn;
        cc = 0;
        memset(ok, false, sizeof(ok));

        do {
          vn = Stack[--top];
          Belong[vn] = block;
          Instack[vn] = false;
          ok[vn] = true;
          tmp[cc++] = vn;
        } while (vn != v);

        ok[u] = 1;
        memset(color, -1, sizeof(color));

        if (!dfs(u, 0)) {
          can[u] = true;

          while (cc--) {
            can[tmp[cc]] = true;
          }
        }
      }
      */
    } else if (Instack[v] && Low[u] > DFN[v]) {
      Low[u] = DFN[v];
    }
  }

  /* 有向图targan
  if (Low[u] == DFN[u]) {
    scc++;

    do {
      v = Stack[--top];
      Instack[v] = false;
      Belong[v] = scc;
      num[scc]++;
    } while (v != u);
  }
  */
}
