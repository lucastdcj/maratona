#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

#define MAXN 128
#define INF 0x3f3f3f3f

int adj[MAXN][MAXN], nadj[MAXN], n, m;

int x[MAXN][MAXN], cap[MAXN][MAXN], r[MAXN][MAXN];
int vis[MAXN], pred[MAXN], delta[MAXN];
int s, t;

int aumenta() {
  int u;
  queue<int> Q;
  memset(vis, 0, sizeof(vis));
  vis[s] = 1; pred[s] = -1; delta[s] = INF;
  Q.push(s);
  while (!Q.empty()) {
    u = Q.front(); Q.pop();
    if (u == t) break;
    for (int i = 0; i < nadj[u]; i++) {
      int v = adj[u][i];
      if (!vis[v] && r[u][v] > 0) {
	vis[v] = 1; pred[v] = u;
	delta[v] = min(delta[u], r[u][v]);
	Q.push(v);
      }
    }
  }
  if (u != t) return 0;
  while (pred[u] != -1) {
    x[pred[u]][u] += delta[t]; r[pred[u]][u] -= delta[t];
    x[u][pred[u]] -= delta[t]; r[u][pred[u]] += delta[t];
    u = pred[u];
  }
  return delta[t];
}

int maxflow() {
  int inc, res = 0;
  /* constroi lista de adjacencias */
  memset(nadj, 0, sizeof(nadj));
  memset(x, 0, sizeof(x));
  memcpy(r, cap, sizeof(r));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (cap[i][j] || cap[j][i]) adj[i][nadj[i]++] = j;
  while ((inc = aumenta()) > 0)
    res += inc;
  return res;
}

int main() {
  int i, cases = 1;
  int u, v, c;

  for (;;) {
    scanf("%d", &n);
    if (!n) break;
    memset(cap, 0, sizeof(cap));
    scanf("%d%d%d", &s, &t, &m); s--; t--;
    for (i = 0; i < m; i++) {
      scanf("%d%d%d", &u, &v, &c); u--; v--;
      cap[u][v] += c;
      cap[v][u] += c;
    }
    printf("Network %d\n", cases++);
    printf("The bandwidth is %d.\n\n", maxflow());
  }

  return 0;
}
