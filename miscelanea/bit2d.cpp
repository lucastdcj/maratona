/*%
  Binary Indexed Tree/Fenwick Tree 2D
  Autor: Marcelo Galvão Póvoa
  Complexidade: O(lg*lg MAX) - atualizacao e consulta
  Tempo de implementacao: 3 min
  Testes: SPOJ.MATSUM
    Descricao: Dada uma matriz inicial vazia, eh possivel fazer
  incremento no conteudo m[x,y] e consultar a soma da
  submatriz m[1..x,1..y] de forma eficiente. Para o cal
  culo da soma de uma submatriz qualquer usa-se a relacao
  sum(a..b,c..d) =  sum(1..b,1..d) + sum(1..a-1,1..c-1)
  - sum(1..b,1..c-1) - sum(1..a-1,1..d)
                           
  Observacao: Zerar a matriz tree[][] antes de utilizar
  %*/

#include <stdio.h>
#include <string.h>
#define MAX 1000

int tree[MAX+1][MAX+1]; /*nao usar posicao em 0*/

int query(int x, int y) {
  int sum=0,yy=y;
  if (x==0 || y==0) return 0;
   
  while (x) {
    while (y) {
      sum+=tree[x][y];
      y-=y & (-y);
    }
    x-=x & (-x);
    y=yy;
  }
  return sum;
}

/*v representa um inc/decremento em x,y!*/
void update(int x, int y, int v) { 
  int yy=y;
  if (x==0 || y==0) return;
   
  while (x<=MAX) {
    while (y<=MAX) {
      tree[x][y]+=v;
      y+=y & (-y);
    }
    x+=x & (-x);
    y=yy;
  }
}

/**** Exemplo simples de uso ****/
int main(){
  memset(tree,0,sizeof(tree));
   
  update(3,5,2);
  update(2,3,-1);
   
  printf("%d\n",query(10,10));
  return 0;
}
