#include <algorithm>		// min()
#include <cstring> 		// memset()
#include <cstdio>

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
  int i, j, u, k, v;
  
  while (scanf("%d", &n) == 1) {
    m = 0;
    memset(nadj, 0, sizeof(nadj));
    for (i = 0; i < n; i++) {
      scanf("%d (%d)", &u, &k);
      for (j = 0; j < k; j++) {
	scanf("%d", &v);
	adj[u][nadj[u]] = v; aresta[u][nadj[u]++] = m;
	adj[v][nadj[v]] = u; aresta[v][nadj[v]++] = m++;
      }
    }
    bcc();
    int nbridge = 0;
    for (i = 0; i < n; i++)
      for (j = 0; j < nadj[i]; j++)
	if (bridge[aresta[i][j]] && i < adj[i][j]) nbridge++;
    printf("%d critical links\n", nbridge);
    for (i = 0; i < n; i++)
      for (j = 0; j < nadj[i]; j++) if (bridge[aresta[i][j]] && i < adj[i][j]) {
	  printf("%d - %d\n", i, adj[i][j]);
	}
    printf("\n");
  }

  return 0;
}
