/*%
Menor Ancestral Comum (LCA)
Autor: Igor Assis / Marcelo Galvão Póvoa
Complexidade: O(n log n) + O(1) por query
Testes: nuevo.2045
Dependencias: Range Minimum Query
Descricao: Dada uma arvore preprocessa de forma a 
           realizar querys da forma LCA(u,v) que retornam
           o menor ancestral (mais longe da raiz) comum
           de u e v na arvore.
Tutorial: 
%*/

#include <cstring>
#include <vector>

using namespace std;

#define MAXNN (2*1024) // usar o dobro do limite

/* FILL ME */
vector<int> adj[MAXN];

int nE, nL, E[MAXN], L[MAXN], R[MAXN], vis[MAXN];

void euler(int u, int el) {
  E[nE++] = u; L[nL++] = el;
  vis[u] = 1;
  for (int i = 0; i < adj[u].size(); i++)
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
  for (i = 2 * n - 2; i >= 0; i--) R[E[i]] = i;
  init(L, nL);
}

int lca(int u, int v) {
  return E[query(min(R[u],R[v]), max(R[u], R[v]))];
}

#include <cstdio>

/**** Exemplo simples de uso ****/
int main(){
  int i, u, v, n;
  scanf("%d", &n);
  for (i = 0; i < n-1; i++) {
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  preprocess(0, n);
  printf("%d\n", lca(2, 3));

  return 0;
}
