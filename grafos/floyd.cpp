#include <cstdio>
#include <cstring>

using namespace std;

typedef long long int64;

#define MAXN 150
#define INF 0x3f3f3f3f

/* FIILL ME */
int custo[MAXN][MAXN]; // matriz de adj com os custos

int d[MAXN][MAXN];
int pai[MAXN][MAXN]; /* pai de j nos caminhos a partir de i */

void floyd(int n) {
  memset(d, 0x3f, sizeof(d));
  for (int i = 0; i < n; i++) 
    for (int j = 0; j < n; j++) 
      if (custo[i][j] < INF) {
        d[i][j] = custo[i][j];
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
    memset(custo, 0, sizeof(custo));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        scanf("%d", &custo[i][j]);        
      }       
    }
    floyd(n);
  }
  return 0;
}
