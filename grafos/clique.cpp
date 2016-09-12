/*%
Cliques Maximais
Autor: Douglas Santos
Complexidade: O(3^(n/3))
Testes: SRM571-div1-550
Descricao: Acha todas as cliques maximais de um grafo.
%*/

#include <cstring>
#include <algorithm>
using namespace std;

typedef long long int int64;

#define MAXN 55
#define INF 0x3f3f3f3f

/* FILL ME */
int n;
/* matriz de adj representada por mascara de bits */
int64 adj[MAXN]; 

void clique(int64 r, int64 p, int64 x) {
  if (p == 0 && x == 0) {         
    /* r é uma clique maximal */
    return;
  }
  int pivot = -1;
  int menor = INF;
  for (int i = 0; i < n; i++) {
    if ( ((1LL << i) & p) || ((1LL << i) & x) ) {
      int x = __builtin_popcountll(p & (~(adj[i])));
      if (x < menor) { 
        pivot = i;
        menor = x;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    if ((1LL << i) & p) {
      if (pivot != -1 && adj[pivot] & (1LL << i)) continue;
      clique(r | (1LL << i), p & adj[i], x & adj[i]);
      p = p ^ (1LL << i);
      x = x | (1LL << i);
    }
  }
}

/**** Exemplo simples de uso ****/
int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    adj[i] = 0;
    for (int j = 0; j < n; j++) {
      int x;
      scanf("%d", &x);
      if (x == 1) adj[i] |= (1LL << j);
    }
  }
  clique(0, (1LL << n) - 1, 0);
  return 0;
}
