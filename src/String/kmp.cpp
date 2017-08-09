// Copyright [2017] <dmnsn7@gmail.com>

#include <bits/stdc++.h>

char *s, *f;
void getFail() {
  int m = strlen(s);
  f[0] = f[1] = 0;

  for (int i = 1; i < m; i++) {
    int j = f[i];

    while (j && s[i] != s[j]) {
      j = f[j];
    }

    f[i + 1] = s[i] == s[j] ? j + 1 : 0;
  }
}

int main() { return 0; }
