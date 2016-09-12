/*%
  Binary Indexed Tree with range update 
  Autor: Douglas Oliveira Santos
  Complexidade: O(lg n) - atualizacao e consulta
  Testes: poj-3468
    Descricao: Dada um vetor inicial vazio, eh possivel fazer
  incremento no conteudo v[a, b] e consultar a soma do
  subvetor v[0..x] de forma eficiente. Para  soma acumulada
  do intervalo [a, b], utilize query(b) - query(a-1)
                           
  Observacao: Zerar o vetor tr[] antes de utilizar
              Pode usar o índice 0
  %*/

typedef long long int int64;
#define MAXN 100010

int64 tr[MAXN][2];
int n;

/* Função interna, não deve ser chamada 
   externamente */
void up(int at, int64 mul, int64 add) {
  while (at < n) {
    tr[at][0] += mul;
    tr[at][1] += add;
    at |= (at + 1);
  }
}

/* Soma by em todos elementos no 
   intervalo [a, b] */
void update(int a, int b, int64 by) {
  up(a, by, -by * (a-1));
  up(b, -by, by * b);
}

/* Retorna a soma acumulada do 
   intervalo [0, at] */
int64 query(int at) {
  int64 mul = 0;
  int64 add = 0;
  int s = at;
  while (at >= 0) {
    mul += tr[at][0];
    add += tr[at][1];
    at = (at & (at + 1)) - 1;
  }
  return mul * s + add;
}

/**** Exemplo simples de uso ****/
#include <cstdio>
#include <cstring>

int main(){
  n = 10;
  memset(tr,0,sizeof(tr));
   
  /* soma 10 no intervalo [0, 5] */
  update(0, 5, 10);
  /* soma 2 no intervalo [6, 6] */
  update(6, 6, 2);
  /* imprime soma acumulada [0, 6] */
  printf("%lld\n",query(6));
  /* imprime soma acumulada [1, 6] */
  printf("%lld\n",query(6) - query(0));
  return 0;
}
