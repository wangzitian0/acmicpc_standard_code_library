int r[maxn], wa[maxn], wb[maxn], wv[maxn], ws[maxn], sa[maxn];
int rank[maxn], height[maxn];

/*
 *处理长度为n的串，其中字符的有效长度为n-1，结尾加0
 *sa数组表示排第几的是谁，有效部分为sa[1]~sa[n]
 *rank表示她排第几，有效部分为rank[0]~rank[n-1],与字符对应
 *height表示第i大与第i-1大串的公共前缀，有效部分2~n，与sa对应
 */

inline bool cmp(int *r, int a, int b, int l) {
  return r[a] == r[b] && r[a + l] == r[b + l];
}

void da(int n, int m) {
  int i, j, p, *x = wa, *y = wb;

  for (i = 0; i < m; i++) {
    ws[i] = 0;
  }

  for (i = 0; i < n; i++) {
    ws[x[i] = r[i]]++;
  }

  for (i = 1; i < m; i++) {
    ws[i] += ws[i - 1];
  }

  for (i = n - 1; i >= 0; i--) {
    sa[--ws[x[i]]] = i;
  }

  for (j = 1, p = 1; p < n; j <<= 1, m = p) {
    for (p = 0, i = n - j; i < n; i++) {
      y[p++] = i;
    }

    for (i = 0; i < n; i++)
      if (sa[i] >= j) {
        y[p++] = sa[i] - j;
      }

    for (i = 0; i < n; i++) {
      wv[i] = x[y[i]];
    }

    for (i = 0; i < m; i++) {
      ws[i] = 0;
    }

    for (i = 0; i < n; i++) {
      ws[wv[i]]++;
    }

    for (i = 1; i < m; i++) {
      ws[i] += ws[i - 1];
    }

    for (i = n - 1; i >= 0; i--) {
      sa[--ws[wv[i]]] = y[i];
    }

    swap(x, y);

    for (p = 1, x[sa[0]] = 0, i = 1; i < n; i++) {
      x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
    }
  }

  return;
}

void calheitght(int n) {
  int i, j, k = 0;

  for (i = 1; i < n; i++) {
    rank[sa[i]] = i;
  }

  // print(rank, n);
  for (i = 0; i < n; height[rank[i++]] = k)
    for (k ? k-- : 0, j = sa[rank[i] - 1]; r[i + k] == r[j + k]; k++)
      {}

  return;
}
