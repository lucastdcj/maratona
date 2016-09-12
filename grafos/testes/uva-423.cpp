/* 
N = 100
Tempo de Execução 0.010
*/

#include <iostream>
#include <queue>
#include <limits.h>

using namespace std;

#define MAXN 101 //numero maximo de vertices
#define INF INT_MAX //nao ha perigo de overflow

int graph[MAXN][MAXN]; //lista de adj
int custo[MAXN][MAXN]; //tamanho das arestas (se refere a aresta da lista graph)
int nadj[MAXN]; //grau de cada vertice
int pai[MAXN]; //para reconstruir o caminho
int dist[MAXN]; //distancia da origem ateh cada vertice
bool used[MAXN];

//parametro to eh opcional, se nao for passado o algoritmo
//retorna a distancia do vertice conectado e mais longe da
//origem
int dijkstra(int n, int s, int to = -1) {
  priority_queue<pair<int, int> > q;
  int a,v;
  int cost, nv = 0;
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
    if (to == a) return dist[a];
    used[a] = true;
    nv++;
    for (int i = 0; i < nadj[a]; i++) {
      v = graph[a][i];
      if (used[v]) continue;
      cost = dist[a] + custo[a][i];
      if (cost >= dist[v]) continue;
      dist[v] = cost;
      q.push(make_pair(-1*cost,v));
      pai[v] = a;
    }
  }
  if (to == -1) to = a;
  return dist[to];
}

int main() {
  int n;
  int cost;
  int far;
  char c[2];
  scanf("%d",&n);
  memset(nadj,0,sizeof(nadj));
  for (int i = 0; i < n; i++) graph[i][i] = 0;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (scanf("%d",&cost) != 1) {
	scanf("%s",c);
	continue;
      }
      custo[i][nadj[i]] = cost;
      custo[j][nadj[j]] = cost;
      graph[i][nadj[i]++] = j;
      graph[j][nadj[j]++] = i;
    }
  }
  far =dijkstra(n,0);
  printf("%d\n",far);
  return 0;
}
