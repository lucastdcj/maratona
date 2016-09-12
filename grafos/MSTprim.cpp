/*%
  Árvore Geradora Mínima (Prim)
  Autor: Davi Costa
  Complexidade: O(m*logn)
  Tempo de implementacao: ?
  Testes: uva.10034
  Descricao: Encontra Arvore Geradora Minima
  %*/

#include <queue>
#include <limits.h>
#include <cstdio>
#include <cstring>

using namespace std;

#define MAXN 101 //numero maximo de vertices
#define INF INT_MAX //nao ha perigo de overflow

/* FILL ME */
int adj[MAXN][MAXN]; //lista de adj
int custo[MAXN][MAXN]; //tamanho das arestas de adj
int nadj[MAXN]; //grau de cada vertice

int pai[MAXN]; //para reconstruir o caminho
int dist[MAXN]; //distancia de cada vertice a arvore
bool used[MAXN];

/*
  n: numero de vertices, s: origem (opcional)
  retorna peso total da arvore
*/
int prim(int n, int s = 0) {
  priority_queue<pair<int, int> > q;
  int a,v;
  int cost, nv = 0;
  int ret = 0;
  memset(pai,-1,sizeof(pai));
  memset(used,0,sizeof(used));
  for (int i = 0; i < n; i++) dist[i] = INF;
  dist[s] = 0;
  pai[s] = s;
  q.push(make_pair(0,s));
  while(!q.empty() && nv < n) {
    a = q.top().second; q.pop();
    if (used[a]) continue;
    ret += dist[a];
    used[a] = true;
    nv++;
    for (int i = 0; i < nadj[a]; i++) {
      v = adj[a][i];
      if(!used[v]){
        cost = custo[a][i];
        if (cost >= dist[v]) continue;
        dist[v] = cost;
        q.push(make_pair(-1*cost,v));
        pai[v] = a;
      }     
    }
  }
  return ret;
}

/**** Exemplo simples de uso ****/
int main() {
  int n, m;
  int from, to, cost;
  while (scanf("%d %d",&n,&m) == 2 && n != 0) {
    memset(nadj,0,sizeof(nadj));
    for (int i = 0; i < m; i++) {
      scanf("%d %d %d",&from,&to,&cost);
      custo[from][nadj[from]] = custo[to][nadj[to]] = cost;
      adj[from][nadj[from]++] = to;
      adj[to][nadj[to]++] = from;
    }
    printf("%d\n",prim(n));
  }
  return 0;
}
