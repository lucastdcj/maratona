#include <cstdio>
#include <cstring>

#include <queue>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 2*123

int A[MAXN][MAXN], nadj[MAXN], n, m;

int x[MAXN][MAXN], cap[MAXN][MAXN], r[MAXN][MAXN];
int e[MAXN], d[MAXN], s, t;

queue<int> Q;

#define adm(u, v) (d[u] == d[v] + 1)

void push(int u, int v, int c) {
  x[u][v] += c;  x[v][u] -= c;
  r[u][v] -= c;  r[v][u] += c;
  e[u] -= c;     e[v] += c;
}

void preprocess() {
  memset(x, 0, sizeof(x));
  memset(e, 0, sizeof(e));
  memset(d, 0, sizeof(d));
  for (int i = 0; i < nadj[s]; i++) {
    int v = A[s][i];
    push(s, v, cap[s][v]);
    if (v != s && v != t) Q.push(v);
  }
  d[s] = n;
}

void push_relabel(int u) {
  int j = -1;
  for (int i = 0; i < nadj[u]; i++) {
    int v = A[u][i];
    if (e[u] <= 0) break;
    if (adm(u, v) && r[u][v] > 0) {
      int delta = min(e[u], r[u][v]);
      push(u, v, delta);
      if (e[v] > 0 && v != s && v != t) Q.push(v);
    }
    if (r[u][v] > 0 && (j == -1 || d[v] < d[j])) j = v;
  }
  if (e[u] > 0) {
    d[u] = d[j] + 1;
    Q.push(u);
  }
}

int maxflow() {
  int flow = 0;
  memcpy(r, cap, sizeof(r));
  preprocess();
  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    push_relabel(u);
  }
  for (int i = 0; i < nadj[s]; i++)
    flow += x[s][A[s][i]];
  return flow;
}

int main() {
  int i, j;
  int b, d, u, v, c;

  while (scanf("%d", &n) == 1) {
    if (!n) break;
    memset(cap, 0, sizeof(cap));
    memset(nadj, 0, sizeof(nadj));
    for (i = 1; i <= n; i++) {
      scanf("%d", &c);
      cap[2*i-1][2*i] += c;
    }
    scanf("%d", &m);
    for (i = 0; i < m; i++) {
      scanf("%d%d%d", &u, &v, &c);
      cap[2*u][2*v-1] += c;
    }
    s = 0;
    t = 2*n+1;
    n = 2*n+2;
    scanf("%d%d", &b, &d);
    for (i = 0; i < b; i++) {
      scanf("%d", &u);
      cap[s][2*u-1] = INF;
    }
    for (i = 0; i < d; i++) {
      scanf("%d", &u);
      cap[2*u][t] = INF;
    }
    for (i = 0; i < n; i++)
      for (j = i+1; j < n; j++)
	if (cap[i][j] || cap[j][i]) {
	  A[i][nadj[i]++] = j;
	  A[j][nadj[j]++] = i;
	}
    printf("%d\n", maxflow());
  }
  
  return 0;
}
