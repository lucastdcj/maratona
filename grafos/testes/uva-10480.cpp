#include <cstdio>

#include <cstring>
#include <queue>

using namespace std;

#define MAXN 100

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

/* funcoes para encontar um s-t-corte minimo */
#define MAXM 10*MAXN

int mark[MAXN], cut[MAXM];

void dfs(int u) {
  mark[u] = 1;
  for (int i = 0; i < nadj[u]; i++)
    if (!mark[A[u][i]] && r[u][A[u][i]] > 0)
      dfs(A[u][i]);
}

void mincut() {
  memset(mark, 0, sizeof(mark));
  dfs(s);
  for (int i = 0; i < n; i++)
    if (mark[i])
      for (int j = 0; j < nadj[i]; j++)
	if (!mark[A[i][j]]) printf("%d %d\n", i+1, A[i][j]+1);
}

/* especifico do problema */
int main() {
  int i;

  for (;;) {
    scanf("%d%d", &n, &m);
    if (!n && !m) break;
    memset(cap, 0, sizeof(cap));
    memset(nadj, 0, sizeof(nadj));
    for (i = 0; i < m; i++) {
      int u, v, c;
      scanf("%d%d%d", &u, &v, &c);
      u--; v--;
      cap[u][v] = cap[v][u] = c;
      A[u][nadj[u]++] = v;
      A[v][nadj[v]++] = u;
    }
    s = 0; t = 1;
    maxflow();
    mincut(); printf("\n");    
  }

  return 0;
}
