/*%
Dijkstra
Autor: Davi Costa
Complexidade: O(m*logn)
Tempo de implementacao: ?
Testes: spoj.SHPATH, uva.423
Descricao: Encontra caminho minimo em grafos com pesos >= 0
%*/

#include <queue>
#include <cstring>
using namespace std;

#define MAXN 101
#define INF INT_MAX //nao ha perigo de overflow

/* FILL ME */
int adj[MAXN][MAXN], nadj[MAXN]; //lista de adj
int cus[MAXN][MAXN]; //tamanho das arestas de adj

int dist[MAXN]; //distancia da origem ateh cada vertice
bool used[MAXN];
//int pai[MAXN]; //Caso queira reconstruir o caminho

// preenche o vetor de distancias dist
void dijkstra(int n, int s) {
  priority_queue<pair<int, int> > q;

  //memset(pai,-1,sizeof(pai));
  memset(used,0,sizeof(used));
  for (int i = 0; i < n; i++) dist[i] = INF;
  dist[s] = 0;
  //pai[s] = s;

  q.push(make_pair(0,s));
  while (!q.empty()) {
    int a = q.top().second;
    q.pop();

    if (used[a]) continue;
    used[a] = true;

    for (int i = 0; i < nadj[a]; i++) {
      int v = adj[a][i];
      int cost = dist[a] + cus[a][i];
      if (cost >= dist[v]) continue;
      dist[v] = cost;
      q.push(make_pair(-1*cost,v));
      //pai[v] = a;
    }
  }
}

/**** Exemplo simples de uso ****/
int main() {
  int n, m;
  int origem,destino;
  int from, to, cost;
  while (scanf("%d %d",&n,&m) == 2 && n != 0) {
    scanf("%d %d",&origem,&destino);
    memset(nadj,0,sizeof(nadj));
    for (int i = 0; i < m; i++) {
      scanf("%d %d %d",&from,&to,&cost);
      cus[from][nadj[from]] = cus[to][nadj[to]] = cost;
      adj[from][nadj[from]++] = to;
      adj[to][nadj[to]++] = from;
    }
    dijkstra(n,origem);

    printf("%d\n",dist[destino]);
  }
  return 0;
}
