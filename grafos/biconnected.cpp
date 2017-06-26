#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

typedef pair<int, int> ii;

#define MAXN 200010

// INPUT
int n, m;
vector<int> adj[MAXN];

// AUX
bool vis[MAXN];
int num[MAXN], low[MAXN];
vector<int> pilha;

// OUTPUT
int ncomp;
vector<int> comps[MAXN]

void dfs(int u, int p, int& t) {
  vis[u] = true;
  num[u] = low[u] = t++;
  pilha.push_back(u);
  for (size_t i = 0; i < adj[u].size(); i++) {
    int v = adj[u][i];
    if (v == p)  continue;
    if (vis[v]) {
      low[u] = min(low[u], num[v]);
    }
    else {
      dfs(v, u, t);
      low[u] = min(low[u], low[v]);
      if (low[v] > num[u]) IS_BRIDGE(u, v);
      if (low[v] >= num[u] && (num[u] > 0 || num[v] > 1)) IS_ART(u);
      if (low[v] >= num[u]) {
        comps[ncomp].push_back(u);
        while (pilha.back() != v) {
          comps[ncomp].push_back(pilha.back());
          pilha.pop_back();
        }
        ncomp++;
      }
    }
  }
}

void bcc() {
  int t;
  ncomp = 0;
  for (int i = 0; i < n; i++) vis[i] = false;
  for (int i = 0; i < n; i++) if (!vis[i]) dfs(i, -1, t = 0);
}
