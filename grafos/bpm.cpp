/*%
Emparelhamento Máximo e Cobertura Mínima
Autor: Igor Assis / Douglas Santos
Complexidade: O(n*m)
Testes: uva.11419, uva.10080, cf-227d
Descricao: Encontra um emparelhamento máximo e uma cobertura
de vértice mínima em grafo bipartido.
Para um grafo bipartido: 
- |cobertura mínima de vertices| = |emparelhamento máximo|
- |conj. independente máximo| = n - |emparelhamento máximo|
- |cobertura mínima de arestas| = n - |emparelhamento máximo|
%*/

#include <cstring>
#include <vector>
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

/**** Exemplo simples de uso ****/
#include <cstdio>

int main() {
  int i, u, v, n, m;

  scanf("%d %d", &n, &m);
  for(int i = 0; i < n; i++) adj[i].clear();
  for (i = 0; i < m; i++) {
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  printf("Matching Maximo/Cobertura Minima: %d\n", minbpec(n));
  printf("Arestas do Matching:\n");
  for (i = 0; i < n; i++)
    if (conj[i] != -1)
      printf("%d %d ", i, conj[i]);
  printf("\nVertices na cobertura:\n");
  for (i = 0; i < n; i++)
    if (cover[i])
      printf("%d ", i);
  printf("\n");

  return 0;
}
