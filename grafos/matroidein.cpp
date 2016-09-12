/*%
Intersecção de Matróides
Autor: Igor Assis
Complexidade: O(|I|*B(n,m)), |I| = tamanho interseccao
                             B(n,m) = complexidade da busca
Tempo de implementacao: ?
Testes: spojbr.HONESTID (|I| = n, B(n,m) = O(mnlog^*n))
Descricao: Encontra a interseccao de dois matroides.
           Esta implementado o caso especifico de
           matroide floresta e matroide cor de aresta unica.
%*/

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

#define MAXN 128
#define MAXM 128*128

#define MAXK 2*MAXN

/* FILL ME */
int n, m, ncor;
int orig[MAXM], dest[MAXM], firma[MAXM];

int p[MAXM], mark[MAXM], comp[MAXN], rank[MAXN];
int nX1, nX2, nY, nX_Y, cor[MAXK];

int X2[MAXM], X1[MAXM], inX2[MAXM], inX1[MAXM];
int Y[MAXM], X_Y[MAXM], inY[MAXM], inX_Y[MAXM];

int find(int u) {
  if (u == comp[u])
    return u;
  return comp[u] = find(comp[u]);
}

void unite(int u, int v)  {
  if (rank[u] > rank[v])
    comp[v] = u;
  else {
    comp[u] = v;
    if (rank[u] == rank[v])
      rank[v]++;
  }
}

int caminho() {
  int i;
  queue<int>Q;

  memset(mark, 0, sizeof(mark));
  for (i = 0; i < nX1; i++) {
    p[X1[i]] = -1;
    mark[X1[i]] = 1;
    if (inX2[X1[i]] != -1)
      return X1[i];
    Q.push(X1[i]);
  }

  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    if (inX2[u] != -1)
      return u;
    if (inY[u] == -1) {
      /* monta ciclo em uma componente */
      if (find(orig[u]) == find(dest[u])) {

        for (i = 0; i < nY; i++)
          if (!mark[Y[i]] &&
              find(orig[Y[i]]) == find(orig[Y[u]])) {
            p[Y[i]] = u;
            mark[Y[i]] = 1;
            if (inX2[Y[i]] != -1)
              return Y[i];
            Q.push(Y[i]);
          }
      } else {
        for (i = 0; i < nY; i++)
          if (!mark[Y[i]]) {
            p[Y[i]] = u;
            mark[Y[i]] = 1;
            if (inX2[Y[i]] != -1)
              return Y[i];
            Q.push(Y[i]);
          }
      }
    } else {
      for (i = 0; i < nX_Y; i++)
        if (!mark[X_Y[i]] &&
            (firma[u] == firma[X_Y[i]] || !cor[firma[u]])) {
          p[X_Y[i]] = u;
          mark[X_Y[i]] = 1;
          if (inX2[X_Y[i]] != -1)
            return X_Y[i];
          Q.push(X_Y[i]);
        }
    }
  }

  return -1;
}

int matroide() {
  int i, u, res;
  nX2 = nX1 = m; nY = 0;
  for (i = 0; i < m; i++) { 
    inX2[i] = X2[i] = inX1[i] = X1[i] = i;
    inY[i] = -1;
  }
  for (i = 0; i < n; i++) {comp[i] = i; rank[i] = 1;}
  memset(cor, 0, sizeof(cor));

  res = 0;
  while ((u = caminho()) != -1) {
    while (u != -1) {
      /* ou-exclusivo */
      if (inY[u] == -1) {
        Y[nY] = u;
        inY[u] = nY++;
        X_Y[inX_Y[u]] = X_Y[--nX_Y];
        inX_Y[X_Y[nX_Y]] = inX_Y[u];
        cor[firma[u]] = 1; /* marca firma */
      } else {
        X_Y[nX_Y] = u;
        inX_Y[u] = nX_Y++;
        Y[inY[u]] = Y[--nY];
        inY[Y[nY]] = inY[u];
        cor[firma[u]] = 0; /* desmarca firma */
      }
      u = p[u];
    }
    /* atualiza componentes */
    for (i = 0; i < n; i++) {comp[i] = i; rank[i] = 1;}
    for (i = 0; i < nY; i++)
      unite(find(orig[Y[i]]), find(dest[Y[i]])); 
    /* atualiza X2 e X1 */
    nX2 = nX1 = 0;
    memset(inX2, -1, sizeof(inX2));
    memset(inX1, -1, sizeof(inX1));
    for (i = 0; i < m; i++) {
      if (inY[i] == -1 && find(orig[i]) != find(dest[i])) {
        X2[nX2] = i;
        inX2[i] = nX2++;
      }
      if (inY[i] == -1 && !cor[firma[i]]) {
        X1[nX1] = i;
        inX1[i] = nX1++;
      }
    }
    res++;
  }
  return res;
}

/* Exemplo e' o problema HONESTID do spojbr */
int main() {
  int i, cases = 1;

  while (scanf("%d%d%d", &n, &m, &ncor) == 3) {
    for (i = 0; i < m; i++) {
      scanf("%d%d%d", &orig[i], &dest[i], &firma[i]);
      orig[i]--; dest[i]--;
    }
    printf("Instancia %d\n", cases++);
    if (matroide() == n-1)
      printf("sim\n\n");
    else printf("nao\n\n");
  }

  return 0;
}
