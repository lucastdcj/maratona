/*%
Fluxo Máximo de Custo Mínimo (Uso Geral) - Corte Mínimo
Autor: Codeforces / Marcelo Galvão Póvoa / Douglas Santos
Complexidade: O(m*Flow), em média, O(m*n*Flow) pior caso
Testes: uva.10594, cf.277E, cf.164C, cf.78E, uva.10480
Descricao: Calcula fluxo usando caminhos aumentantes usando
SPFA (um Bellman-Ford otimizado), suporta arestas múltiplas
e não direcionadas (usar add() 2x), usa lista de adjacências
eficiente em um único vetor e sem STL. Para max-cost, use ar-
estas de custo negativo (mas sem ciclo negativo). Se todos os
custos são iguais, o algoritmo equivale ao Edmonds Karp. Se
quiser obter o fluxo em cada aresta i, use re[2*i+1] e para
obter o residual use re[2*i]. Aresta i: ve[2*i+1] -> ve[2*i]
%*/

#include <algorithm>
using namespace std;

#define N 201
#define M (2*1010) // dobro do número de arestas
#define INF 0x3f3f3f3f

int vt, ve[M], re[M], ze[M], next[M];
int in[N], head[N], path[N], dis[N], qu[N], lim[N];

void init() {
  vt = 1;
  memset(head, 0, sizeof(head));
}

void add(int x, int y, int cap, int wei = 0) {
  // aresta x->y é armazenada em [vt+1] e [vt+2]
  ve[++vt] = y; re[vt] = cap; ze[vt] = wei;
  next[vt] = head[x]; head[x] = vt;
  ve[++vt] = x; re[vt] = 0; ze[vt] = -wei;
  next[vt] = head[y]; head[y] = vt;
}

int mfmc(int s, int t, int n, int &fcost) {
  int flow = fcost = 0;
  while (1) {
    int qt = 0, k = 0;
    qu[qt++] = s;
    for (int i = 0; i < n; i++)
      dis[i] = lim[i] = INF;
    dis[s] = 0;
    
    while (k != qt) {
      if (k == N) k = 0;
      int x = qu[k++];
      for (int i = head[x]; i; i = next[i]) // ve[i]: adjs de x
        if (re[i] && dis[x] + ze[i] < dis[ve[i]]){
          dis[ve[i]] = dis[x] + ze[i];
          path[ve[i]] = i;
          lim[ve[i]] = min(lim[x], re[i]);
          if (!in[ve[i]]) {
            if (qt == N) qt = 0;
            qu[qt++] = ve[i];
            in[ve[i]] = 1;
          }
        }
      in[x] = 0;
    }
    
    if (dis[t] == INF) break;
    int f = lim[t];
    for (int p = t; p != s; p = ve[path[p] ^ 1]) {
      re[path[p]] -= f; re[path[p] ^ 1] += f; // novo residual
    }
    fcost += f * dis[t];
    flow += f;
  }
  return flow;
}

/** Código abaixo apenas para Min Cut **/

/* mark[v] = true, se v esta no mesmo lado de u no corte */
bool mark[N];

void DFS(int u) {
  mark[u] = true;
  for (int i = head[u]; i; i = next[i]) {
    if (i % 2) continue;
    int v = ve[i];
    if (!mark[v] && re[i] > 0) {
      DFS(v);
    }
  }
 }

void mincut(int s, int t, int n) {
  memset(mark, 0, sizeof(mark));
  DFS(s);
  /* Arestas do corte */
  for (int i = 0; i < n; i++)
    for (int j = head[i]; j; j = next[j]) {
      if (j % 2) continue;
      int v = ve[j];
      if (mark[i] && !mark[v])
        printf("%d %d\n", i, v);
    }
}

/**** Exemplo simples de uso ****/
int main() {
  int n, m;
  while (scanf("%d %d",&n,&m) == 2) {
    int from, to, cp, co;
    init();
    for (int i = 0; i < m; i++) {
      scanf("%d %d %d %d",&from,&to,&cp, &co);
      add(from, to, cp, co);
    }
    int s=0, t=1;
    int fcost, flow=mfmc(s,t,n,fcost);
    printf("Fluxo: %d\nCusto: %d\n",flow,fcost);

    for (int i = 1; i <= m; i++) {
      printf("f(%d->%d) = %d\n",ve[2*i+1],ve[2*i],re[2*i+1]);
      printf("r(%d->%d) = %d\n",ve[2*i+1],ve[2*i],re[2*i]);
    }

    mincut(s, t, n);
  }
  return 0;
}
