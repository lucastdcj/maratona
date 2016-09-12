/*%
  Eliminação de Gauss
  Autor: Marcelo Galvão Póvoa
  Complexidade: O(n^3)
  Testes: poj-3756
    Descricao: Calcula, se existir, a inversa mi da matriz
  ma com pivoteamento, sendo inicialmente mi a identidade.
  Pode ser usado colocando uma matriz-coluna de constantes
  em mi para se obter a solução do sistema linear.
  %*/

#include <cmath>
#include <algorithm>
using namespace std;
#define MAXN 100

double ma[MAXN][MAXN], mi[MAXN][MAXN];

bool invert(int n) {
  for (int k=0; k<n; k++) {
    int imax=k;
    for (int i=k+1; i<n; i++)
      if (fabs(ma[i][k]) > fabs(ma[imax][k])) imax=i;

    double p = ma[imax][k];
    if (fabs(p) < 1e-8) return false;
    
    for (int j=0; j<n; j++) {
      swap(ma[k][j], ma[imax][j]);
      swap(mi[k][j], mi[imax][j]);
      ma[k][j] /= p; mi[k][j] /= p;
    }

    for (int i=0; i<n; i++) {
      if (i == k) continue;
      double mul = ma[i][k];
      for (int j=0; j<n; j++) {
        ma[i][j] -= ma[k][j]*mul;
        mi[i][j] -= mi[k][j]*mul;
      }
    }
  }
  return true;
}

/**** Exemplo simples de uso ****/
int main() {
  int n;

  scanf("%d",&n);
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++) {
      scanf("%lf",&ma[i][j]);
      mi[i][j] = (i==j)?1.0:0.0;
    }

  if (!invert(n)) printf("singular\n");
  else {
    for (int i=0; i<n; i++) {
      for (int j=0; j<n-1; j++)
        printf("%.1lf ", mi[i][j]);
      printf("%.1lf\n", mi[i][n-1]);
    }
  }
  return 0;
}
