#include <cstring>
#include <vector>
#include <cstdio>
using namespace std;
#define MAXN 2024

/* Input - FILL ME */
vector<int> adj[MAXN];
/* Output */
int conj[MAXN]; // conj[u] = v, se v for emparelhado com u
int cor[MAXN];  // cor[u] = partição do vertice u (0 ou 1)
/* Variavel auxiliar */
int vis[MAXN];

/* Função auxiliar */
bool DFS(int u, int c) {
  cor[u] = c;
  for (int i = 0; i < (int) adj[u].size(); i++) {
    int v = adj[u][i];
    if (cor[v] == c) return false;
    if (cor[v] == -1) {
      if (!DFS(v, c^1)) return false;
    }
  }
  return true;
}

/* Função auxiliar */
int aumenta(int u) {
  int i;
  for (i = 0; i < (int) adj[u].size(); i++) {
    int v = adj[u][i];
    if (vis[v]) continue; vis[v] = 1;
    if (conj[v] == -1 || aumenta(conj[v])) {
      conj[v] = u;
      conj[u] = v;
      return 1;
    }
  }
  return 0;
}

int maxbpm(int n) {
  int i;
  int res = 0;
  memset(cor, -1, sizeof(cor));
  for (int i = 0; i < n; i++) {
    if (cor[i] == -1) 
      if (!DFS(i, 0)) return -1; // grafo não é bipartido
  }
  memset(conj, -1, sizeof(conj));
  for (i = 0; i < n; i++) {
    if (cor[i]) continue;
    memset(vis, 0, sizeof(vis));
    if (aumenta(i)) res++;
  }
  return res;
}

/* Código apenas para cobertura mínima de vertice */

/* Output */
bool cover[MAXN]; //cover[i] -> vertice i pertence a cobertura

/* Função auxiliar */
void reach(int u) {
  int i;
  vis[u] = 1;
  for (i = 0; i < (int) adj[u].size(); i++) {
    int v = adj[u][i];
    if (!vis[v] && ((conj[u] != v && !cor[u]) ||
                    (conj[u] == v && cor[u]))) reach(v);
  }
}

int minbpec(int n) {
  int i;
  int res = maxbpm(n);
  memset(vis, 0, sizeof(vis));
  for (i = 0; i < n; i++) {
    if (cor[i]) continue;
    if (!vis[i] && conj[i] == -1) reach(i);
  }
  /* C = (U \ Rm) \/ (V /\ Rm) */
  memset(cover, false, sizeof(cover));
  for (i = 0; i < n; i++) {
    if (!vis[i] && !cor[i]) cover[i] = true;
    if (vis[i] && cor[i]) cover[i] = true;
  }
  return res;
}

int main() {
  int u, v;
  int r, c, N;
  int n;
  for (;;) {
    scanf("%d%d%d", &r, &c, &N);
    if (!r && !r && !N) break;
    n = r + c;
    for (int i = 0; i < n; i++) adj[i].clear();
    for (int i = 0; i < N; i++) {
      scanf("%d%d", &u, &v); u--; v = v-1+r;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    printf("%d", minbpec(n));
    for (int i = 0; i < r; i++)
      if (cover[i]) printf(" r%d", i+1);
    for (int i = r; i < n; i++)
      if (cover[i]) printf(" c%d", i-r+1);
    printf("\n");
  }

  return 0;
}
