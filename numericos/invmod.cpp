/*%
  Inverso Modular
  Autor: NU2/Marcelo Galvão Póvoa
  Complexidade: O(lg x)
  Tempo de implementacao: 3 min
  Testes: SPOJ.DIOFANTO
  Descricao: Calcula um x tal que a*x === 1 (mod M)
  Para a e M coprimos, eh garantido que x eh unico
  Nesse caso, pode ser usado para determinar
  a divisao modular como exemplificado.
%*/
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

pll mdc(int a, int b){
  if (b == 0) return pll(1LL, 0LL);
  pll u = mdc(b, a % b);
  return pll(u.second, u.first - (a / b) * u.second);
}

ll invmod(ll a, ll M) {
  pll r = mdc(a,M);
  if (r.first * a + r.second * M == 1)
    return (r.first + M) % M;
  return 0LL;
}

#include <cstdio>
/**** Exemplo simples de uso ****/
int main() {
  int x,m;
   
  scanf(" %d %d",&x,&m);
   
  /*retorna 36/x (mod m), se x eh divisor de 36*/
  //printf("%d\n",36*invmod(x,m) % m);
  printf("%lld\n",invmod(x,m));
  return 0;
}
