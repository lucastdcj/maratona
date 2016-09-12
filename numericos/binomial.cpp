/*%
  Binomial Modular (e não modular)
  Autor: Alexandre Kunieda
  Complexidade: binomial: O(n)*O(lg MOD);  binomial_: O(n)
  Testes: binomial: DIOFANTO;  binomial_: uva.530, uva.369
  Dependencias: binomial: inverso modular;  binomial_: nenhuma
  Descricao: binomial(n,k,M) calcula o binomial C(n,k)%M sem
  overflow, utilizando inverso modular;  binomial_(n,k) deter-
  mina qualquer C(n,k) que caiba em um int (menor que 2^31-1)
%*/

#define MOD 1300031
typedef long long int64;

int64 fat(int64 n, int64 M = MOD) {
  int64 i, fat = 1;
  for(i=2 ; i<=n ; i++)
    fat = (fat*i)%M;
  return fat;
}

int64 binomial(int64 n, int64 k, int64 M = MOD) {
  int64 a = fat(n)*invmod(fat(k),M);
  int64 b = invmod(fat(n-k),M);
  return ( (a%M)*b )%M;
}


int64 binomial_(int n, int k) {
  if(n-k < k) k = n-k;
  if(k == 0) return 1;
  return (n-k+1)*binomial_(n,k-1)/k;
}

/**** Exemplo simples de uso ****/
#include <stdio.h>
#define MAX 10

int main() {
  for(int i=0 ; i<MAX ; ++i) {
    for(int j=0 ; j<=i ; ++j)
      printf("%lld ", binomial(i,j));
    putchar('\n');
  }

  for(int i=0 ; i<MAX ; ++i) {
    for(int j=0 ; j<=i ; ++j)
      printf("%lld ", binomial_(i,j));
    putchar('\n');
  }

  return 0;
}
