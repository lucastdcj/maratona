#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define MAXN 100123

int n, m;
int nadj[MAXN], mark[MAXN], napilha[MAXN];
vector<int> adj[MAXN];
int comp[MAXN], vis[MAXN], stck[MAXN], t, high[MAXN], num, ncomp;

void dfscc(int u) {
  int i, v;
  high[u] = vis[u] = num--;
  stck[t++] = u;
  for (i = 0; i < nadj[u]; i++) {
    v = adj[u][i];
    if (!vis[v]) {
      dfscc(v);
      high[u] = max(high[u], high[v]);
    } else if (vis[v] > vis[u] && !comp[v])
      high[u] = max(high[u], vis[v]);
  }
  if (high[u] == vis[u]) {
    ncomp++;
    do {
      v = stck[--t];
      comp[v] = ncomp;
    } while (v != u);
  }
}

void scc() {
  int i;
  ncomp = t = 0; num = n;
  memset(vis, 0, sizeof(vis));
  memset(comp, 0, sizeof(comp));
  for (i = 0; i < n; i++)
    if (!vis[i])
      dfscc(i);
}

int cactus(int u) {
  int i, vn = 0;
  mark[u] = napilha[u] = 1;
  for (i = 0; i < nadj[u]; i++) {
    int v = adj[u][i];
    if (napilha[v]) vn++;
    if (vn > 1) return 0;
    if ((mark[v] && !napilha[v]) || (!mark[v] && !cactus(v)))
      return 0;
  }
  napilha[u] = 0;
  return 1;
}

int main() {
  int nt;
  int i;

  scanf("%d", &nt);
  while (nt--) {
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++) adj[i].clear();
    for (i = 0; i < m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      adj[u].push_back(v);
    }
    for (i = 0; i < n; i++)
      nadj[i] = adj[i].size();
    scc();
    memset(napilha, 0, sizeof(napilha));
    memset(mark, 0, sizeof(mark));
    if (ncomp > 1 || !cactus(0))
      printf("NO\n");
    else printf("YES\n");
  }

  return 0;
}
