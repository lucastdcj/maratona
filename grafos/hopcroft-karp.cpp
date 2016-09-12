/*%
  Emparelhamento Máximo Bipartido O(sqrt(n) * m)
  Autor: Douglas Santos
  Complexidade: O(sqrt(n) * m)
  Testes: timus-1229, timus-1389
  Descricao: Encontra um emparelhamento máximo 
  *          em grafo bipartido.
  %*/

#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

#define MAXN 100010
#define NIL 0
#define INF 0x3f3f3f3f

/* FILL ME */
/* U = {1, 2, ..., nu), V = {nu+1, nu+2, ..., nv) */
int nu, nv;         
vector< int > G[MAXN];

int match[MAXN], dist[MAXN];

bool bfs() {
  int i, u, v, len;
  queue< int > Q;
  for(i=1; i<=nu; i++) {
    if(match[i]==NIL) {
      dist[i] = 0;
      Q.push(i);
    }
    else dist[i] = INF;

  }

  dist[NIL] = INF;
  while(!Q.empty()) {
    u = Q.front(); Q.pop();
    if(u!=NIL) {
      len = G[u].size();
      for(i=0; i<len; i++) {
        v = G[u][i];
        if(dist[match[v]]==INF) {
          dist[match[v]] = dist[u] + 1;
          Q.push(match[v]);
        }
      }
    }
  }

  return (dist[NIL]!=INF);

}
     
bool dfs(int u) {
  int i, v, len;
  if(u!=NIL) {
    len = G[u].size();
    for(i=0; i<len; i++) {
      v = G[u][i];
      if(dist[match[v]]==dist[u]+1) {
        if(dfs(match[v])) {
          match[v] = u;
          match[u] = v;
          return true;
        }
      }
    }

    dist[u] = INF;
    return false;
  }

  return true;

}
     
int hopcroft_karp() {
  int matching = 0, i;
  while(bfs())
    for(i=1; i<=nu; i++)
      if(match[i]==NIL && dfs(i))
        matching++;
  return matching;
}

/* Exemplo simples de uso */
int main() {
  int m,a,b;
  scanf("%d %d %d",&nu,&nv,&m);
  for (int i=0; i<m; i++) {
    scanf("%d %d",&a,&b);
    b += nu;
    G[a].push_back(b);
    G[b].push_back(a);
  }

  printf("%d\n",hopcroft_karp());
    
  /* Imprime MATCH */
  for (int u = 1; u <= nu; u++) {
    if (match[u]) printf("%d %d\n", u, match[u]);
  }
  return 0;
}
