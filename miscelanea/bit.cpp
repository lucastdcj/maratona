/*%
  Binary Indexed Tree/Fenwick Tree
  Autor: Marcelo Galvão Póvoa
  Complexidade: O(lg MAX) - atualizacao e consulta
  Testes: SPOJ.ORDERS, SPOJ.INCDSEQ
    Descricao: Dada um vetor inicial vazio, eh possivel fazer
  incremento no conteudo v[x] e consultar a soma do
  subvetor v[0..x] de forma eficiente. Para o calculo
  da soma de um subvetor qualquer usa-se a relacao
  sum(a..b) =  sum(1..b) - sum(1..a-1)
                           
  Observacao: Zerar o vetor tree[] antes de utilizar
  %*/

#define MAXN 1000

int tree[MAXN+1];

int query(int x) {
  int sum=0;
   
  for (x++; x>0; x-=x & (-x))
    sum+=tree[x];

  return sum;
}

/*by representa um inc/decremento em x*/
void update(int x, int by) { 
  if (x<0) return;
   
  for (x++; x<=MAXN; x+=x & (-x))
    tree[x]+=by;
}

/**** Exemplo simples de uso ****/
#include <cstdio>
#include <cstring>

int main(){
  memset(tree,0,sizeof(tree));
   
  update(3,2);
  update(2,-1);
   
  printf("%d\n",query(10));
  return 0;
}
