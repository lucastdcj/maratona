/*%
Árvore Geradora de Diâmetro Mínimo
Autor: Igor Assis
Complexidade: O(n^2 + mn^2) 
Tempo de implementacao: ?
Testes: spoj.MDST
Descricao: Encontra o diametro da arvore geradora de diametro
           minimo e um absolute 1-center a partir do qual
           da para se obter a arvore.
%*/

#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

#define MAXN 1012
#define INF 0x3f3f3f3f

/* FILL ME */
int n, m;
int adj[MAXN][MAXN], peso[MAXN][MAXN], nadj[MAXN];

int d[MAXN][MAXN], pred[MAXN][MAXN], t[2][MAXN], k[MAXN];
int U, L;

int mark[MAXN];

/* a arvore geradora de diametro minimo é a
   arvore de caminhos minimos a partir do vértices CAC: que é
   um vértice criado a distancia d/2 de _j_ na aresta (i,j) */
struct _CAC {int i, j, d;} CAC;

/* trocar para floyd-warshall se tem pesos nas arestas */
int asp() {
  // all-pairs-shortest-path
  int vc = -1;
  memset(d, 0, sizeof(d));
  memset(k, -1, sizeof(k));
  for (int j = 0; j < n; j++) {
    queue<int> Q;
    memset(mark, 0, sizeof(mark));
    mark[j] = 1;
    pred[j][j] = -1;
    Q.push(j);
    while (!Q.empty()) {
      int u = Q.front(); Q.pop();
      if (k[u] == -1 || d[j][u] > d[j][k[j]]) k[j] = u;
      for (int i = 0; i < nadj[u]; i++)
        if (!mark[adj[u][i]]) {
          Q.push(adj[u][i]);
          pred[j][adj[u][i]] = u;
          d[j][adj[u][i]] = d[j][u] + 1;
          mark[adj[u][i]] = 1;
        }
    }
    if (vc == -1 || d[j][k[j]] < d[vc][k[vc]]) vc = j;
  }
  return vc;
}

int update(int i, int j, int k) {
  int c, delta = t[j][k];
  for (c = 0; c < n; c++) t[j][c] -= delta;
  for (c = 0; c < n; c++)
    if (t[j][c] > 0 && t[i][c] > 0) break;
  if (c == n) {
    U = L;
    CAC.i = i; CAC.j = j; CAC.d = abs(U-2*d[j][k]);
    return 1;
  }
  return 0;
}

int mdst() {
  int j, vc;

  vc = asp();
  U = 2*d[vc][k[vc]];
  CAC.i = -1; CAC.j = vc; CAC.d = 0;

  for (int r = 0; r < n; r++)
    for (int u = 0; u < nadj[r]; u++) if (r < adj[r][u]) {
        int s = adj[r][u];
        if (k[r] == k[s]) continue;
        if ((L = peso[r][u] + d[r][k[s]] + d[s][k[r]]) >= U) 
          continue;
        memcpy(t[0], d[r], sizeof(t[0]));
        memcpy(t[1], d[s], sizeof(t[1]));
        if (update(1, 0, k[s]) || update(0, 1, k[r]))
          continue;
        for (;;) {
          int maxv = -1, maxi, maxj;
          for (j = 0; j < n; j++)
            if ((t[0][j] > 0 && t[1][j] > 0)) {
              if (maxv == -1 || t[0][j] > maxv)
                maxv = t[0][j], maxi = 0, maxj = j;
              if (maxv == -1 || t[1][j] > maxv)
                maxv = t[1][j], maxi = 1, maxj = j;
              }
          L = L + t[1-maxi][maxj];
          if (L >= U) break;
          if(update(maxi, 1-maxi, maxj)) break;
        }
      }
  return U;
}

/**** Exemplo simples de uso ****/
int main(){
  return 0;
}
