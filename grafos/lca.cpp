int depth[MAXN];
int P[MAXLOG][MAXN];

void init(int n) {
  for (int j = 1; (1 << j) < n; j++)
    for (int i = 0; i < n; i++)
      if (P[j - 1][i] != -1) {
        P[j][i] = P[j - 1][P[j - 1][i]]; 
      }
}

int lca(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  for (int i = MAXLOG - 1; i >= 0; i--) {
    if (P[i][u] != -1 && depth[P[i][u]] >= depth[v]) u = P[i][u];
  }
  if (u == v) return v;
  for (int i = MAXLOG - 1; i >= 0; i--) {
    if (P[i][v] != -1 && P[i][u] != P[i][v]) {
      u = P[i][u];
      v = P[i][v];
    }
  }
  return P[0][u];    
}
