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

typedef pair<int,int> pii;

pii mdc(int a, int b){
  if (b == 0) return pii(1,0);
  pii u = mdc (b,a%b);
  return pii(u.second, u.first - (a/b)*u.second);
}

int invmod(int a, int M) {
  pii r=mdc(a,M);
  if (r.first * a + r.second * M == 1)
    return (r.first + M) % M;
  return 0;
}

#include <cstdio>
/**** Exemplo simples de uso ****/
int main() {
  int x,m;
   
  scanf(" %d %d",&x,&m);
   
  /*retorna 36/x (mod m), se x eh divisor de 36*/
  //printf("%d\n",36*invmod(x,m) % m);
  printf("%d\n",invmod(x,m));
  return 0;
}
