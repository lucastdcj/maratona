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
typedef long long ll;

ll fat(ll n, ll M = MOD) {
  ll i, fat = 1;
  for(i = 2LL ; i <= n ; i++)
    fat = (fat * i) % M;
  return fat;
}

ll binomial(ll n, ll k, ll M = MOD) {
  ll a = fat(n) * invmod(fat(k), M);
  ll b = invmod(fat(n - k), M);
  return ((a % M) * b) % M;
}


ll binomial_(int n, int k) {
  if (n - k < k) k = n - k;
  if (k == 0) return 1LL;
  return (n - k + 1LL) * binomial_(n, k - 1LL) / k;
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
