/*%
Union Find e Árvore Geradora Mínima (Kruskal)
Autor: Douglas Santos / topcoder forum
Complexidade: Union-Find: O(1), Kruskal: O(m*lgn)
Descricao: Estrutura de dados union find e uma aplicação
para encontrar a árvore geradora mínima
%*/

#include <algorithm>
using namespace std;

#define MAXN 1010

int id[MAXN], sz[MAXN]; //uf auxiliar

void ufinit(int n) {
  for (int i = 0; i < n; i++)
    id[i] = i, sz[i] = 1;
}

int uffind(int i) {
  if (i == id[i]) return i;
  return id[i] = uffind(id[i]);
}

void ufunion(int v, int w) {
  v = uffind(v); w = uffind(w);
  if (v == w) return;
  if (sz[v] > sz[w]) swap(v, w);
  id[v] = w;
  if (sz[v] == sz[w]) sz[w]++;
}

/* MST - Kruskal a partir daqui */
#define MAXM 10010

/* FILL ME */
struct Edge {
  int u, v, w;
  int ind;
} ed[MAXM];

bool comp(const Edge& a, const Edge& b) {
  return a.w < b.w;
}

/* Para cada aresta i, 
diz se está ou não na árvore */
bool used[MAXM];
int kruskal(int n, int m) {
  sort(ed, ed + m, comp);
  ufinit(n);
  int res = 0;
  for (int i = 0; i < m; i++) {
    int u = uffind(ed[i].u);
    int v = uffind(ed[i].v);
    if (u == v) {
      used[ed[i].ind] = false;
      continue;
    }
    used[ed[i].ind] = true;
    ufunion(u, v);
    res += ed[i].w;
  }
  return res;
}
