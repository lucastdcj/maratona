#define MAXN ...

vector<int> adj[MAXN];

bool vis[MAXN];
int t, num[MAXN], low[MAXN];

void dfs(int u, int p = -1) {
  vis[u] = true;
  num[u] = low[u] = t++;
  for (size_t i = 0; i < adj[v].size(); i++) {
    int v = adj[u][i];
    if (v == u)  continue;
    if (vis[v]) {
      low[u] = min(low[u], num[v]);
    }
    else {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] > num[u]) IS_BRIDGE(u, v);
    }
  }
}

void find_bridges() {
  t = 0;
  for (int i = 0; i < n; i++) vis[i] = false;
  for (int i = 0; i < n; i++) if (!vis[i]) dfs(i);
}
