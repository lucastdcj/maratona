/*%
  Euclides Extendido
  Autor: NU 2/Marcelo Galvão Póvoa
  Complexidade: O(lg x)
  Tempo de implementacao: 1 min
  Testes: SPOJ.DIOFANTO
    Descricao: Calcula um par x,y tal que a*x+b*y=mdc(a,b)
%*/
#include <algorithm>
using namespace std;

typedef pair<int,int> pii;

pii mdc(int a, int b){
  if (b == 0) return pii(1,0);
  pii u = mdc (b,a%b);
  return pii(u.second, u.first - (a/b)*u.second);
}

/**** Exemplo simples de uso ****/
int main(){
  int a,b;
  pii euext;
   
  scanf(" %d %d",&a,&b);
  euext=mdc(a,b);
   
  printf("%d %d\n",euext.first,euext.second);
  return 0;
}
