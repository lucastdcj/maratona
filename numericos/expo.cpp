/*%
Exponenciação modular rápida
Autor: Douglas Oliveira Santos
Complexidade: O(log(b))
Descricao: Dado a, b e m, calcula a^b mod m
%*/

#include <cstdio>
#include <cstring>

using namespace std;

typedef long long int ll;

ll expo(ll a, ll b, ll m = MOD) {
  ll y = a % m, x = 1;
  while (b > 0) {
    if (b % 2 == 1) {
      x = (x*y) % m;
    }
    y = (y*y) % m;
    b = b/2;
  }
  return x % m;    
}

/**** Exemplo simples de uso ****/
int main() {
  ll res;
  res = expo(2, 1000000007-2, 1000000007);
  printf("%lld\n", res);
  return 0;
}
