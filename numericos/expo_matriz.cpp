/*%
  Exponenciação de Matrizes - Fibonnaci
  Autor: Marcelo Galvão Póvoa / Douglas Santos
  Complexidade: O(d^3 log n)
  Testes: SPOJ.RABBIT1
  Descricao: Exponenciação rápida modular de matriz
  e como exemplo cálculo do fibonnaci  
%*/
#include <cstring>
#define MOD 1000000
#define MAXD 2
using namespace std;

typedef long long int64;
typedef int64 mat[MAXD][MAXD];

void mul(mat &c, mat &a, mat &b, int d) {
  mat r = {{0,}};

  for (int i=0;i<d;i++)
    for (int j=0;j<d;j++)
      for (int k=0;k<d;k++) {
        r[i][j] += (a[i][k] * b[k][j]) % MOD;
        r[i][j] %= MOD;
      }

  memcpy(c,r,sizeof(r));
}

/* res = (a^n) % mod, d = dimensão da matriz */
void expo(mat &res, mat &a, int64 n, int d = MAXD) {
  mat y, x;
  memcpy(y, a, sizeof(a));
  memset(x, 0, sizeof(x));
  for (int i = 0; i < d; i++) x[i][i] = 1;

  for (n--; n>0; n/=2) {
    if (n % 2) mul(x,x,y,d);
    mul(y,y,y,d);
  }
  memcpy(res, x, sizeof(x));
}

/**** Exemplo simples de uso ****/
/* Cálculo do fibonacci */
int main() {
  int64 n;
  mat a = {{1, 1}, {1, 0}};
  while (scanf(" %lld",&n)==1) {
    mat f;
    expo(f, a, n);
    printf("%lld\n",(f[0][0] + f[0][1]) % MOD);
  }
  return 0;
}
