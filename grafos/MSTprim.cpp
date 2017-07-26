#include <queue>
#include <limits.h>
#include <cstdio>
#include <cstring>

using namespace std;

typedef pair<int, int> pii;

#define MAXN 101 //numero maximo de vertices
#define INF INT_MAX //nao ha perigo de overflow

/* FILL ME */
vector<int> adj[MAXN]; //lista de adj
vector<int> custo[MAXN]; //tamanho das arestas de adj

int pai[MAXN]; //para reconstruir o caminho
int dist[MAXN]; //distancia de cada vertice a arvore
bool used[MAXN];

/*
  n: numero de vertices, s: origem (opcional)
  retorna peso total da arvore
*/
int prim(int n, int s = 0) {
  priority_queue<pii> q;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    dist[i] = INF;
    used[i] = false;
    pai[i] = -1;
  }
  dist[s] = 0;
  pai[s] = s;
  q.push(pii(0, s));
  while(!q.empty()) {
    int u = q.top().second; q.pop();
    if (used[u]) continue;
    ans += dist[u];
    used[u] = true;
    for (int i = 0; i < adj[u]size(); i++) {
      int v = adj[u][i];
      if (used[v] || custo[u][i] >= dist[v]) continue;
      dist[v] = custo[u][i]; pai[v] = u;
      q.push(pii(-cost, v));
    }     
  }
  return ans;
}

/**** Exemplo simples de uso ****/
int main() {
  int n, m;
  int from, to, cost;
  while (scanf("%d %d",&n, &m) == 2 && n != 0) {
    for (int i = 0; i < m; i++) {
      scanf("%d %d %d",&from,&to,&cost);
      adj[from].push_back(to); custo[from].push_back(cost);
      adj[to].push_back(from); custo[to].push_back(cost);
    }
    printf("%d\n",prim(n));
  }
  return 0;
}
