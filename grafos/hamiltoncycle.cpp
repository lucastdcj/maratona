/*%
  Ciclo Hamiltoniano de Custo Mínimo
  Autor: Alexandre Kunieda + Prefield
  Complexidade: O(n^2 * 2^n)
  Testes: uva.11643
    Descricao: Resolve o problema do caixeiro viajante.
Para obter um ciclo de custo mínimo, descomente os trechos
comentados do código.
%*/

#include <vector>
using namespace std;

#define MAXN 18
#define INF 0x3f3f3f3f

/* FILL ME */
int n;
int graph[MAXN][MAXN]; //matriz de adjacências

int X[MAXN][1<<MAXN];
// int Y[MAXN][1<<MAXN];
// vector<int> path;

// void rec(int i, int S) {
//   if(S) rec(Y[i][S], S & ~(1<<i));
//   path.push_back(i);
// }

int tsp(int s=0) {
  int N = 1<<n;

  for(int i=0 ; i<n ; i++)
    for(int j=0 ; j<N ; j++) {
      X[i][j] = INF;
      //Y[i][j] = -1;
    }

  for(int i=0 ; i<n ; i++) {
    X[i][1<<i] = graph[s][i];
    //Y[i][1<<i] = s;
  }

  for(int S=1 ; S<N ; S++)
    for(int i=0 ; i<n ; i++) {
      if(!(S & (1<<i))) continue;
      for(int j=0 ; j<n ; j++) {
        if(S & (1<<j)) continue;
        if(X[j][S|(1<<j)] > X[i][S]+graph[i][j]) {
          X[j][S|(1<<j)] = X[i][S]+graph[i][j];
          //Y[j][S|(1<<j)] = i;
        }
      }
    }

  //path.clear();
  //rec(s, N-1);
  return X[s][N-1];
}

/**** Exemplo simples de uso ****/
#include <cstdio>
#include <cstring>

int main() {
  memset(graph, 0x3f, sizeof(graph));

  n = 3;
  graph[0][1] = 1;
  graph[1][2] = 3;
  graph[2][0] = 2;

  printf("%d\n", tsp());

  return 0;
}
