#include <iostream>
#include <queue>
#include <limits.h>
#include <map>
#include <string>
#include <vector>

#define pb push_back

using namespace std;

#define MAXN 10123 //numero maximo de vertices
#define INF INT_MAX //nao ha perigo de overflow

vector<int> graph[MAXN]; //lista de adj
vector<int> custo[MAXN]; //tamanho das arestas (se refere a aresta da lista graph)
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

/**** Exemplo simples de uso ****/
int main() {
  int k;
  int n, l, t;
  int to, cost;
  map<string,int> m;
  string s1, s2;
  scanf("%d",&k);
  while (k) {
    k--;
    m.clear();
    memset(nadj,0,sizeof(nadj));
    scanf("%d",&n);
    for (int i = 0; i <= n; i++) {
      custo[i].clear();
      graph[i].clear();
    }
    for (int i = 1; i <= n; i++) {
      cin >> s1;
      m[s1] = i;
      scanf("%d",&l);
      for (int j = 0; j < l; j++) {
	scanf("%d %d",&to,&cost);
	custo[i].pb(cost);
	graph[i].pb(to);
	nadj[i]++;
      }
    }
    scanf("%d",&t);
    for (int i = 0; i < t; i++) {
      cin >> s1 >> s2;
      printf("%d\n",dijkstra(n+1,m[s1],m[s2]));
    }
  }
  return 0;
}
