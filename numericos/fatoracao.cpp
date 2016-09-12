/*%
  Fatoração de Número Inteiro
  Autor: Felipe Sodre
  Complexidade: O(log N)
  Tempo de implementacao: 1 minuto
  Testes: todo(fsodre)
  Dependencias: 
      - Crivo de Erastotenes
  Descricao: 
     fatora(n, arr) coloca no array arr todos os fatores
     primos de n, nao necessariamente em ordem. Retorna
     a quantidade de fatores primos.
%*/

#include <iostream>
#include <cstdio>

/**
   Crivo aqui
**/

inline int div(int n){
  if(pr[n]) return n;
  return divisor[n];
}

int fatora(int n, int fatores[]){
  if(n <= 1){
    fatores[0] = n;
    return 0;
  }

  int k = 0;
  while(n > 1){
    fatores[k++] = div(n);
    n /= div(n);
  }
  return k;
}

/**** Exemplo simples de uso ****/
int main(void){
  int nums[15];

  crivo(500);

  int qt = fatora(444, nums);
  for(int i = 0; i < qt; i++){
    printf("%d eh um fator de 444.\n",nums[i]);
  }

  return 0;
}
