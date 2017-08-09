// Copyright [2017] <dmnsn7@gmail.com>

#include <bits/stdc++.h>

using std::queue;
using std::vector;

struct CH {
  int fail, isend;
  vector<int> next;
  void init() {}
};

vector<CH> ch;

int sz = 0;
queue<int> q;
void init() {
  sz = 1;
  ch[0].init();
}

void build() {
  queue<int> q;
  ch[0].fail = 0;

  for (int c = 0; c < 4; c++) {
    int u = ch[0].next[c];

    if (u) {
      ch[u].fail = 0;
      q.push(u);
    }
  }

  while (!q.empty()) {
    int r = q.front();
    q.pop();

    for (int c = 0; c < 4; c++) {
      int u = ch[r].next[c];

      if (!u) {
        ch[r].next[c] = ch[ch[r].fail].next[c];
        continue;
      }

      q.push(u);
      int v = ch[r].fail;

      while (v && !ch[v].next[c]) {
        v = ch[v].fail;
      }

      ch[u].fail = ch[v].next[c];
      ch[u].isend |= ch[ch[u].fail].isend;
    }
  }
}

int main() { return 0; }
