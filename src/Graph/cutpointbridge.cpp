// Copyright [2017] <dmnsn7@gmail.com>

#include <bits/stdc++.h>

const int MAXN = 10010;
const int MAXM = 100010;
struct Edge {
  int to, next;
  bool cut;  // 是否为桥的标记
} edge[MAXM];
int head[MAXN], tot;
int Low[MAXN], DFN[MAXN], Stack[MAXN];
int Index, top;
bool Instack[MAXN];
bool cut[MAXN];
int add_block[MAXN];  // 删除一个点后增加的连通块
int bridge;
void addedge(int u, int v) {
  edge[tot].to = v;
  edge[tot].next = head[u];
  edge[tot].cut = false;
  head[u] = tot++;
}
void Tarjan(int u, int pre) {
  Low[u] = DFN[u] = ++Index;
  Stack[top++] = u;
  Instack[u] = true;
  int son = 0;

  for (int i = head[u]; i != -1; i = edge[i].next) {
    int v = edge[i].to;

    if (v == pre) {
      continue;
    }

    if (!DFN[v]) {
      son++;
      Tarjan(v, u);

      if (Low[u] > Low[v]) {
        Low[u] = Low[v];
      }

      if (Low[v] > DFN[u]) {  // 桥
        bridge++;
        edge[i].cut = true;
        edge[i ^ 1].cut = true;
      }

      if (u != pre && Low[v] >= DFN[u]) {  // 割点不是树根
        cut[u] = true;
        add_block[u]++;
      }
    } else if (Low[u] > DFN[v]) {
      Low[u] = DFN[v];
    }

    /* 边双联通
     * else if( Instack[v] && Low[u] > DFN[v] )
     *     Low[u] = DFN[v];
     * }
     * if(Low[u] == DFN[u]){
     *     block++;
     *     do
     *     {
     *         v = Stack[--top];
     *         Instack[v] = false;
     *         Belong[v] = block;
     *     }while( v!=u );
     * }
     */
  }

  if (u == pre && son > 1) {
    cut[u] = true;  // 树根,分支数大于1
  }

  if (u == pre) {
    add_block[u] = son - 1;
  }

  Instack[u] = false;
  top--;
}
void solve(int N) {
  memset(DFN, 0, sizeof(DFN));
  memset(Instack, false, sizeof(Instack));
  memset(add_block, 0, sizeof(add_block));
  memset(cut, false, sizeof(cut));
  Index = top = 0;
  bridge = 0;

  for (int i = 1; i <= N; i++)
    if (!DFN[i]) {
      Tarjan(i, i);
    }

  printf("%d critical links\n", bridge);
}
void init() {
  tot = 0;
  memset(head, -1, sizeof(head));
}

int main() {
  return 0;
}
