#include <iostream>
#include <queue>
#include <limits.h>
#include <math.h>

using namespace std;

#define MAXN 110 //numero maximo de vertices
#define INF 1e100 //nao ha perigo de overflow

//graph e custo pode ser modificado pra vector sem alterar o algoritmo
int graph[MAXN][MAXN]; //lista de adj
double custo[MAXN][MAXN]; //tamanho das arestas (se refere a aresta da lista graph)
int nadj[MAXN]; //grau de cada vertice
int pai[MAXN]; //para reconstruir o caminho
double dist[MAXN]; //distancia de cada vertice a arvore
bool used[MAXN];

/*
n: numero de vertices, s: origem (opcional)
retorna peso total da arvore
*/
double prim(int n, int s = 0) {
  priority_queue<pair<double, int> > q;
  int a,v;
  int nv = 0;
  double cost;
  double ret = 0;
  memset(pai,-1,sizeof(pai));
  memset(used,0,sizeof(used));
  for (int i = 0; i < n; i++) dist[i] = INF;
  dist[s] = 0;
  pai[s] = s;
  q.push(make_pair(0,s));
  while(!q.empty() && nv < n) {
    a = q.top().second;
    q.pop();
    if (used[a]) continue;
    ret += dist[a];
    used[a] = true;
    nv++;
    for (int i = 0; i < nadj[a]; i++) {
      v = graph[a][i];
      if (used[v]) continue;
      cost = custo[a][i];
      if (cost >= dist[v]) continue;
      dist[v] = cost;
      q.push(make_pair(-1*cost,v));
      pai[v] = a;
    }
  }
  return ret;
}

/**** Exemplo simples de uso ****/
int main() {
  int n, m, k;
  double cost;
  pair<double,double> v[MAXN];
  scanf("%d",&k);
  for (int z = 0; z < k; z++) {
    if (z != 0) printf("\n");
    memset(nadj,0,sizeof(nadj));
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
      scanf("%lf %lf",&v[i].first,&v[i].second);
    }
    for (int i = 0; i < n; i++) {
      for (int j = i+1; j < n; j++) {
	cost = pow(pow(v[i].first - v[j].first,2) + pow(v[i].second - v[j].second,2),.5);
	custo[i][nadj[i]] = custo[j][nadj[j]] = cost;
	graph[i][nadj[i]++] = j;
	graph[j][nadj[j]++] = i;
      }
    }
    printf("%.2lf\n",prim(n));
  }
  return 0;
}
