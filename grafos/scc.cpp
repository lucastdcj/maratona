/*%
Componentes Fortemente Conexas
Autor: Igor Assis
Complexidade: O(n+m)
Testes: uva.247 uva.10510 SPOJ.CARPDAPIO
Descricao: Encontra as componentes fortemente conexas de um
           grafo orientado. Componentes nomeadas de 1 à ncomp.
%*/

#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 1024

/* Input - FILL ME */
vector<int> adj[MAXN];

/* Output */
int ncomp;      // numero de componentes fortemente conexas
int comp[MAXN]; // comp[i] = componente do vertice i

/* Variaveis auxiliares */
int vis[MAXN], stck[MAXN], t, high[MAXN];
int num;

void dfscc(int u) {
  int i, v;
  high[u] = vis[u] = num--;
  stck[t++] = u;
  for (i = 0; i < (int) adj[u].size(); i++) {
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

void scc(int n) {
  ncomp = t = 0; num = n;
  memset(vis, 0, sizeof(vis));
  memset(comp, 0, sizeof(comp));
  for (int i = 0; i < n; i++)
    if (!vis[i]) dfscc(i);
}

/**** Exemplo simples de uso ****/
#include <cstdio>

int main(void){
  int i, u, v, n, m;

  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) adj[i].clear();
  for (i = 0; i < m; i++) {
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
  }

  scc(n);

  printf("Numero componentes: %d\n", ncomp);
  for (i = 0; i < n; i++)
    printf("componente[%d] = %d\n", i, comp[i]);

  return 0;
}
