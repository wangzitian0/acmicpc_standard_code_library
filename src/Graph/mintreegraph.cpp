// Copyright [2017] <dmnsn7>

const int INF = 0x3f3f3f3f;
const int MAXN = 1010;
const int MAXM = 40010;
struct Edge {
  int u, v, cost;
};
Edge edge[MAXM];
int pre[MAXN], id[MAXN], visit[MAXN], in[MAXN];
int zhuliu(int root, int n, int m, Edge edge[]) {
  int res = 0, u, v;

  while (1) {
    for (int i = 0; i < n; i++) {
      in[i] = INF;
    }

    for (int i = 0; i < m; i++)
      if (edge[i].u != edge[i].v && edge[i].cost < in[edge[i].v]) {
        pre[edge[i].v] = edge[i].u;
        in[edge[i].v] = edge[i].cost;
      }

    for (int i = 0; i < n; i++)
      if (i != root && in[i] == INF) {
        return -1;  //不存在最小树形图
      }

    int tn = 0;
    memset(id, -1, sizeof(id));
    memset(visit, -1, sizeof(visit));
    in[root] = 0;

    for (int i = 0; i < n; i++) {
      res += in[i];
      v = i;

      while (visit[v] != i && id[v] == -1 && v != root) {
        visit[v] = i;
        v = pre[v];
      }

      if (v != root && id[v] == -1) {
        for (int u = pre[v]; u != v; u = pre[u]) {
          id[u] = tn;
        }

        id[v] = tn++;
      }
    }

    if (tn == 0) {
      break;  //没有有向环
    }

    for (int i = 0; i < n; i++)
      if (id[i] == -1) {
        id[i] = tn++;
      }

    for (int i = 0; i < m;) {
      v = edge[i].v;
      edge[i].u = id[edge[i].u];
      edge[i].v = id[edge[i].v];

      if (edge[i].u != edge[i].v) {
        edge[i++].cost -= in[v];
      } else {
        swap(edge[i], edge[--m]);
      }
    }

    n = tn;
    root = id[root];
  }

  return res;
}
