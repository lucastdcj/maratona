#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXN 10123

int nadj[MAXN], freq[MAXN];

#define N 100100
#define LOG 16     // piso de log2(N)

int *va, Log2[N], p[LOG+1][N];

int pairmin(int i1, int i2) {
   return va[i1]</*=*/va[i2] ? i1:i2;
}

void init(int *a, int n) {
  va = a;
  for (int i=1,k=0; i<=n; i++) {
    Log2[i] = k;
    if (1 << (k+1) == i) k++;
  }

  int ln = Log2[n];
  for (int i=0; i<n; i++) p[0][i]=i;
  for (int i=1; i<=ln; i++) 
    for (int j=0; j + (1 << i) - 1 < n; j++) {
      int i1 = p[i-1][j];
      int i2 = p[i-1][j+ (1 << i-1)];
      p[i][j] = pairmin(i1, i2);
    }
}
   
int query(int b, int e) {
  int ln = Log2[e - b + 1];
  int i1 = p[ln][b];
  int i2 = p[ln][e - (1 << ln) + 1];
    
  return pairmin(i1,i2);
}

/* FILL ME */
vector<int> adj[N];

int nE, nL, E[N], L[N], R[N], vis[N];

void euler(int u, int el) {
  E[nE++] = u; L[nL++] = el;
  vis[u] = 1;
  for (int i = 0; i < nadj[u]; i++)
    if (!vis[adj[u][i]]) {
      euler(adj[u][i], el+1);
      E[nE++] = u; L[nL++] = el;
    }
}

void preprocess(int root, int n) {
  int i;
  nE = nL = 0;
  memset(vis, 0, sizeof(vis));
  euler(root, 0);
  for (i = 2*n-2; i >= 0; i--) R[E[i]] = i;
  init(L, nL);
}

int lca(int u, int v) {
  return E[query(min(R[u],R[v]), max(R[u], R[v]))];
}

bool cmp(const int &a, const int &b) {
  return freq[a] < freq[b];
}

int main() {
  int i, j, q, n;
  int u, v, m, root;

  while (scanf(" %d", &n) == 1) {
    memset(nadj, 0, sizeof(nadj));
    for (i = 0; i < n; i++) adj[i].clear();
    for (i = 0; i < n; i++) {
      scanf(" %d : ( %d )", &u, &m); u--;
      for (j = 0; j < m; j++) {
	scanf(" %d", &v); v--;
	adj[u].push_back(v);
	adj[v].push_back(u);
      }
      if (i == 0) root = u;
    }
    for (i = 0; i < n; i++) nadj[i] = adj[i].size();
    preprocess(root, n);
    memset(freq, 0, sizeof(freq));
    scanf(" %d", &q);
    for (i = 0; i < q; i++) {
      scanf(" ( %d %d ) ", &u, &v); u--; v--;
      freq[lca(u, v)]++;
    }
    for (i = 0; i < n; i++)
      if (freq[i])
	printf("%d:%d\n", i+1, freq[i]);
  }

  return 0;
}
