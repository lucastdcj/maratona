/*%
Floyd Warshall
Autor: Douglas Oliveira Santos
Complexidade: O(n^3)
Testes: nuevo-5785
Descricao: Encontra o caminho
mínimo entre todos os pares de vértices
%*/

#include <cstdio>
#include <cstring>
using namespace std;

typedef long long int64;

#define MAXN 150
#define INF 0x3f3f3f3f

/* FIILL ME */
int adj[MAXN][MAXN]; // matriz de adj com os custos

int d[MAXN][MAXN];
int pai[MAXN][MAXN]; /* pai de j nos caminhos a partir de i */

void floyd(int n) {
  memset(d, 0x3f, sizeof(d));
  for (int i = 0; i < n; i++) 
    for (int j = 0; j < n; j++) 
      if (adj[i][j] < INF) {
        d[i][j] = adj[i][j];
        pai[i][j] = i;
      }
          
  for (int k = 0; k < n; k++) 
    for (int i = 0; i < n; i++) 
      for (int j = 0; j < n; j++) 
        if (d[i][j] > d[i][k] + d[k][j]) {
          d[i][j] = d[i][k] + d[k][j];
          pai[i][j] = pai[k][j];  
        }
}

/**** Exemplo simples de uso ****/
int main() {
  int n;
  while (1) {
    scanf("%d", &n);
    if (n == 0) return 0;
    memset(adj, 0, sizeof(adj));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        scanf("%d", &adj[i][j]);        
      }       
    }
    floyd(n);
  }
  return 0;
}
