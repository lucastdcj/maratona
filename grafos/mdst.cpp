/*%
Árvore Geradora de Diâmetro Mínimo (+ eficiente)
Autor: Igor Assis
Complexidade: O(n^3 + n^2logn) 
Tempo de implementacao: ?
Testes: spoj.MDST
Descricao: Encontra o diametro da arvore geradora de 
           diametro minimo, mais rapido se só precisa
           do diametro.
%*/

#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

#define MAXN 1123
#define INF 0x3f3f3f3f

/* FILL ME */
int n, m;
int adj[MAXN][MAXN], peso[MAXN][MAXN], nadj[MAXN];

int d[MAXN][MAXN], t[MAXN];
int mark[MAXN];

int mdst() {
  int i, j, k, u;

  if (n == 1)
    return 0;

  // all-pairs-shortest-path
  for (k = 0; k < n; k++) {
    queue<int> Q;
    memset(mark, 0, sizeof(mark));
    d[k][k] = 0;
    mark[k] = 1;
    Q.push(k);
    while (!Q.empty()) {
      u = Q.front(); Q.pop();
      for (i = 0; i < nadj[u]; i++)
        if (!mark[adj[u][i]]) {
          Q.push(adj[u][i]);
          d[k][adj[u][i]] = d[k][u] + 1;
          mark[adj[u][i]] = 1;
        }
    }
  }
  
  // absolute local 1-center
  int H = INF;
  i = 0;
  memset(t, 0, sizeof(t));
  for (u = 0; u < n; u++)
    for (j = 0; j < nadj[u]; j++)
      if (u < adj[u][j]) {
        for (k = 0; k < n; k++) 
          t[i] = max(t[i], min(d[u][k], d[adj[u][j]][k]));
        H = min(H, peso[u][j] + 2*t[i++]); 
      }

  int value = INF;
  i = 0;
  for (u = 0; u < n; u++)
    for (j = 0; j < nadj[u]; j++)
      if (u < adj[u][j] && 2*t[i++] <= H) {
        vector<pair<int, int> > L;
        for (int k = 0; k < n; k++)
          L.push_back(make_pair(d[u][k], d[adj[u][j]][k]));
        sort(L.begin(), L.end(), greater<pair<int, int> > ());
        int p = 0;
        value = min(value, 2*L[0].first);
        for (int k = 0; k < n; k++)
          if (L[p].second < L[k].second)
            value = min(value, peso[u][j] +
                        L[p].second + L[k].first), p = k;
        value = min(value, 2*L[p].second);
      }
  
  return value;
}

/**** Exemplo simples de uso ****/
int main(){
  return 0;
}
