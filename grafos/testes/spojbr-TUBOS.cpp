#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXN 1024
#define MAXM 1024*1024

int n, m;
int adj[MAXN][MAXN], aresta[MAXN][MAXN], nadj[MAXN];

int low[MAXN], part[MAXN], bridge[MAXM];
int dt;

int vis[MAXN];

int dfsbcc(int u, int p) {
  int i, ch = 0;
  vis[u] = dt;
  low[u] = dt++;
  for (i = 0; i < nadj[u]; i++) {
    int v = adj[u][i];
    if (!vis[v]) {
      dfsbcc(v, u); ch++;
      low[u] = min(low[u], low[v]);
      if (low[v] >= vis[u]) part[u] = 1;
      if (low[v] == vis[v]) bridge[aresta[u][i]] = 1;
    } else if (v != p)
      low[u] = min(low[u], vis[v]);
  }
  return ch;
}

void bcc() {
  int i;
  dt = 1;
  memset(low, 0, sizeof(low));
  memset(vis, 0, sizeof(vis));
  memset(part, 0, sizeof(part));
  memset(bridge, 0, sizeof(bridge));
  for (i = 0; i < n; i++)
    if (!vis[i] && dfsbcc(i, -1) >= 2)
      part[i] = 1;
}

int main() {
  int i, j, u, v;

  for (;;) {
    scanf("%d%d", &n, &m);
    if (!n && !m) break;
    memset(nadj, 0, sizeof(nadj));
    for (i = 0; i < m; i++) {
      scanf("%d%d", &u, &v); u--; v--;
      adj[u][nadj[u]] = v; aresta[u][nadj[u]++] = i;
      adj[v][nadj[v]] = u; aresta[v][nadj[v]++] = i;
    }
    bcc();
    for (i = 0; i < n; i++)
      for (j = 0; j < nadj[i]; j++)
	if (bridge[aresta[i][j]]) goto end;
  end:
    if (i == n) printf("S\n");
    else printf("N\n");
  }

  return 0;
}
