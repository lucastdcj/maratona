/* 
N = 100
Tempo de Execução 0.020
*/

#include <iostream>
#include <queue>
#include <limits.h>

using namespace std;

#define MAXN 101 //Numero maximo de vertices
#define MAXM MAXN*MAXN //Numero maximo de arestas
#define INF 0x3f3f3f3f


/* aresta (u,v) com peso w:
   orig[i] = u, dest[i] = v, peso[i] = w
   d[u], distancia da origem s ae o ertice u
*/

int orig[MAXM], dest[MAXM], peso[MAXM], d[MAXN], pai[MAXN];
/* retorna 1 se o grafo nao tem ciclo negativo, 0 c.c */

int bellman_ford(int s, int n, int m) {
  int i, j;
  memset(pai,-1,sizeof(pai));
  pai[s] = s;
  for (i = 0; i < n; i++)
    d[i] = INF;
  d[s] = 0;
  for (i = 0; i < n-1; i++)
    for (j = 0; j < m; j++) {
      int u = orig[j], v = dest[j], w = peso[j];
      if (d[u] > d[v]+w) {
	d[u] = d[v]+w;
	pai[u] = v;
      }
    }
  for (j = 0; j < m; j++) {
    int u = orig[j], v = dest[j], w = peso[j];
    if (d[u] > d[v]+w) return 0;
  }
  return 1;
}


int main() {
  int n;
  int cost;
  int far;
  char c[2];
  scanf("%d",&n);
  int k = 0;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (scanf("%d",&cost) != 1) {
	scanf("%s",c);
	continue;
      }
      orig[k] = i;
      dest[k] = j;
      peso[k] = cost;
      k++;
      orig[k] = j;
      dest[k] = i;
      peso[k] = cost;
      k++;
    }
  }
  bellman_ford(0,n,k);
  far = 0;
  for (int i = 0; i < n; i++) far = max(far,d[i]);
  printf("%d\n",far);
  return 0;
}
