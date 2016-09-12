/*%
  Crivo de Erastótenes
  Autor: Felipe Sodre
  Complexidade: O(N log log N)
  Tempo de implementacao: 2 minutos
  Testes: todo(fsodre)
    Descricao: Popula o array pr, de tal forma que pr[i] eh
  verdadeiro se i eh primo.
%*/

#include <iostream>
#include <cstdio>

// Numero maximo a ser analisado
#define MAXN 1123123

// se pr[i] == true, i eh primo
bool pr[MAXN+1];

// algum divisor primo de i. Para fatoracao.
int divisor[MAXN+1];

// Analisa primalidade no intervalo [1,n]
void crivo(int n) {
  memset(pr, true, n * sizeof(bool));
  pr[0] = pr[1] = false;
  for(int i = 2; i*i <= n; i++){
    if( !pr[i] || !(i&1) && i > 2) continue;
    int k = i*i;
    divisor[i] = i;
    while(k <= n){
      pr[k] = false;
      divisor[k] = i;
      k += i;
    }
  }
}

/**** Exemplo simples de uso ****/
int main(void){
  crivo(500);
  if(pr[2]) printf("2 eh primo\n");
  if(pr[9]) printf("9 eh primo\n");

  return 0;
}
