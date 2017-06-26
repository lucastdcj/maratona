int lca(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  for (int i = LOG; i >= 0; i--) {
    if (p[i][u] != -1 && depth[p[i][u]] >= depth[v]) u = p[i][u];
  }
  if (u == v) return v;
  for (int i = LOG; i >= 0; i--) {
    if (p[i][v] != -1 && p[i][u] != p[i][v]) {
      u = p[i][u];
      v = p[i][v];
    }
  }
  return p[0][u];    
}
