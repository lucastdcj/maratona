/*%
Fluxo Mínimo
Autor: Douglas Santos
Complexidade: O(m*Flow)
Testes: pku-3870
Descricao: Calcula o fluxo mínimo viável entre s e t,
onde cada aresta e do grafo tem um capacidade mínima lb[e] e
máxima ub[e], de forma que o fluxo: lb[e] <= f[e] <= ub[e].
%*/

#include <algorithm>
#include <cstring>
using namespace std;

/* Fluxo Máximo SPFA AQUI */

/* FILL ME */
int lb[N][N], ub[N][N];

int f[N][N];

int minflow(int n, int s, int t) {
  lb[t][s] = 0;
  ub[t][s] = INF;
  init();
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (ub[i][j])
        add(i, j, ub[i][j] - lb[i][j], 0);

  for (int i = 0; i < n; i++) {
    int b = 0;
    for (int j = 0; j < n; j++) {
      b += lb[j][i];
      b -= lb[i][j];
    }
    if (b >= 0)
      add(n, i, b);
    else
      add(i, n+1, -b);
  }
  int fcost;
  mfmc(n, n+1, n+2, fcost);

  for (int i = head[n]; i; i = next[i]) {
    if (i & 1) continue;
    if (re[i] > 0) return -1;
  }

  for (int i = 0; i < n; i++)
    for (int j = head[i]; j; j = next[j]) {
      if (j & 1 || ve[j] != n+1) continue;
      if (re[j] > 0) return -1;
    }

  memcpy(f, lb, sizeof(lb));
  mfmc(t, s, n, fcost);
  int res = 0;
  for (int i = 0; i < n; i++)
    for (int j = head[i]; j; j = next[j]) {
      if (j & 1) continue;
      int v = ve[j];
      f[i][v] += re[j+1];
      if (i == s) res += f[s][v];
    }
  return res;
}

/**** Exemplo simples de uso ****/
#include <cstdio>
int main() {
  int n, m;
  memset(lb, 0, sizeof(lb));
  memset(ub, 0, sizeof(ub));
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    int u, v, a, b;
    scanf("%d %d %d %d", &u, &v, &a, &b);
    lb[u][v] = a;
    ub[u][v] = b;
  }
  int s = 0, t = n-1;
  int res = minflow(s, t, n);

  if (res == -1)
    printf("Fluxo Inviável\n");
  else
    printf("Fluxo Mínimo Viável: %d\n", res);

  return 0;
}
