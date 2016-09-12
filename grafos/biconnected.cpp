/*%
Pontes, Pontos de Articulação e Componentes Biconexas
Autor: Igor Assis / Douglas Santos
Complexidade: O(n+m)
Testes: uva.796 spojbr.TUBOS
Descricao: Encontra as pontes, os pontos de articulacao e as
componentes biconexas (comecando em 1) em um grafo
não direcionado. Não permite arestas múltiplas.
%*/

#include <cstring>
#include <stack>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 1024
#define MAXM 1024*1024

#define VIZ(u, i) (orig[inc[u][i]] != (u) ? \
                   orig[inc[u][i]] : dest[inc[u][i]])

/* Input - FILL ME */
/* aresta i = (u, v); orig[i] = u, dest[i] = v,
   inc[u].push_back(i), inc[v].push_back(i) */
vector<int> inc[MAXN];
int orig[MAXM], dest[MAXM];

/* Output */
int ponte[MAXM]; // ponte[i] -> aresta i é ponte
int part[MAXN]; // part[u] -> vertice u é de articulação
int ncomp; // numero de componentes biconexas
int comp[MAXM]; // comp[i] = componente da aresta i

/* Variaveis auxiliares */
int low[MAXN], vis[MAXN], dt;
stack<int> stck;

/* Função auxiliar */
int dfsbcc(int u, int p) {
  int ch = 0;
  vis[u] = dt++;
  low[u] = vis[u];
  for (int i = 0; i < (int) inc[u].size(); i++) {
    int e = inc[u][i], v = VIZ(u, i);
    if (!vis[v]) {
      stck.push(e);
      dfsbcc(v, u); ch++;
      low[u] = min(low[u], low[v]);
      if (low[v] >= vis[u]) {
        part[u] = 1;
        ncomp++;
        while (stck.top() != e) {
          comp[stck.top()] = ncomp;
          stck.pop();
        }
        comp[stck.top()] = ncomp; stck.pop();
      }
      if (low[v] == vis[v]) ponte[e] = 1;
    } else if (v != p) {
      if (vis[v] < vis[u]) stck.push(e);
      low[u] = min(low[u], vis[v]);
    }
  }
  return ch;
}

void bcc(int n) {
  memset(low, 0, sizeof(low));
  memset(vis, 0, sizeof(vis));
  memset(part, 0, sizeof(part));
  memset(ponte, 0, sizeof(ponte));
  memset(comp, 0, sizeof(comp));
  dt = 1;
  ncomp = 0;
  for (int i = 0; i < n; i++)
    if (!vis[i])
      part[i] = dfsbcc(i, -1) >= 2;
}

#include <cstdio>

int main(){
  int i;
  int n, m;
  scanf("%d%d", &n, &m);

  for (int i = 0; i < m; i++) inc[i].clear();
  for (i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    orig[i] = u; dest[i] = v;
    inc[u].push_back(i);
    inc[v].push_back(i);
  }

  bcc(n);

  printf("Pontos de Articulacao:");
  for (i = 0; i < n; i++)
    if (part[i]) printf(" %d", i);
  printf("\n");
  
  printf("Pontes:");
  for (i = 0; i < m; i++)
      if (ponte[i])
        printf(" (%d %d)", orig[i], dest[i]);
  printf("\n");

  printf("Componentes:\n");
  for (i = 0; i < m; i++)
    printf("comp[%d] = %d\n", i, comp[i]);
  printf("\n");

  return 0;
}
