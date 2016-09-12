/*%
  Operações com Bits
  Autor: Guilherme Kunigami
  Complexidade:
  Tempo de implementacao: 7 min
  Testes:
  - TCCC 2006, Round 1B Medium
  - TCO  2006, Round 1  Easy
  - SRM 320, Division 1 Hard
  %*/

#include <string>
#include <stdlib.h>
using namespace std;

void print_bit(int a, int k){
  for (int i=0, j = (1 << (k-1)); i<k; i++){
    printf("%d", (j&a)?1:0);
    a <<= 1;
  }
  printf("\n");
}
int bitmask(string s){
    return strtol(s.c_str(), NULL, 2);
}

/* Operacoes entre as mascaras de bits a e b, de tamanho k */
void operacoes_bits(int a, int b, int k){

  print_bit(a, k);
  print_bit(b, k);

  int ALL_BITS = (1 << k) - 1;
  /* bit = {0,...,k-1} */
  int bit = 6;

  print_bit(ALL_BITS, k);

  /* Uniao */
  print_bit(a | b, k);
  /* Intersecao */   a & b;
  print_bit(a & b, k);
  /* Subtracao */    a & ~b;
  print_bit(a & ~b, k);
  /* Negacao */
  print_bit(ALL_BITS ^ a, 32);
  /* Limpar o bit setado menos significativo */
  print_bit(a & (a - 1), k);
  /* Seta o 4º bit-esimo menos significativo */
  print_bit(a |= 1 << bit, k);
  /* Limpar o bit-esimo menos significativo */
  print_bit(a &= ~(1 << bit), k);
  /* Testar o bit-esimo menos significativo */
  if (a & 1 << bit)
    printf("Bit setado\n");
  else
    printf("Bit nao setado\n");
}

/* Itera sobre todos os subconjuntos do conjunto
 * representado pela mascara mask. Gera os subconjuntos
 * maiores (em valor de mascara) primeiro */
void subset(int mask, int k){
  for (int i = mask; i > 0; i = (i - 1) & mask)
    print_bit(i, k);
  print_bit(0, k);
}
/* Gera todas as mascaras de tamanho n, com m bits setados */
void comb(int dep, int from, int mask, int n, int m) {
  if (dep == m){
    print_bit(mask, n);
    return;
  }
  // Seta o i-esimo bit e desce
  for (int i = from; i < n; i++)
    comb(dep+1, i+1, mask | (1<<i), n, m);
}

/* Funcoes de bits do gcc */
void builtin(int mask){
  printf("# Bits setados: %d\n", __builtin_popcount(mask));
  //PS.: Depende do tipo do numero!
  printf("# Zeros no comeco: %d\n", __builtin_clz(mask));
  printf("# Zeros no final: %d\n", __builtin_ctz(mask));
}

/*** Exemplo Simples de uso ***/
int main (){
  printf("Principais operacoes de bits\n");
  operacoes_bits(389, 454, 10);

  printf("Gera todos os subconjuntos de 1000110101:\n");
  subset(bitmask("1000110101"), 10);

  printf("Todas as combinacoes 10 escolhe 3:\n");
  comb(0, 0, 0, 10, 3);

  printf("Teste das funcoes builtin do GCC");
  builtin(bitmask("011101011000"));

  return 0;
}
