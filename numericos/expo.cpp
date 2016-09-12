/*%
Exponenciação modular rápida
Autor: Douglas Oliveira Santos
Complexidade: O(log(b))
Descricao: Dado a, b e m, calcula a^b mod m
%*/

#include <cstdio>
#include <cstring>

using namespace std;

typedef long long int int64;

int64 expo(int64 a, int64 b, int64 m) {
  int64 y = a % m, x = 1;
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
int main()
{
  int64 res;
  res = expo(2, 1000000007-2, 1000000007);
  printf("%lld\n", res);
  return 0;
}
