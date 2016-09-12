/*%
  Knight Distance
  Autor: Alexandre Kunieda + TopCoder Forum
  Complexidade: O(1)
  Testes: uva.11643, uva.439, tju.1736
    Descricao: Determina em O(1) a distância (em movimentos de
  cavalo) entre 2 pontos de um tabuleiro (infinito ou finito).
  Se o tabuleiro for finito, deve ter tamanho n x m com
  n >= 4 e m >= 4.
%*/

#include <algorithm>
using namespace std;

int knightdist_inf(int x1, int y1, int x2, int y2) {
  int dx=abs(x2-x1);
  int dy=abs(y2-y1);
  if (abs(dx)==1 && dy==0) return 3;
  if (abs(dy)==1 && dx==0) return 3;
  if (abs(dx)==2 && abs(dy)==2) return 4;

  int lb=max((dx+1)/2, (dy+1)/2);
  lb = max(lb, (dx+dy+2)/3);
  if ((lb%2)!=(dx+dy)%2) lb++;
  return lb;
}

int n,m; //tamanho do tabuleiro

int knightdist(int x1, int y1, int x2, int y2) {
  if(x1==n || x2==n) {
    x1 = n+1 - x1;
    x2 = n+1 - x2;
  }
  if(y1==m || y2==m) {
    y1 = m+1 - y1;
    y2 = m+1 - y2;
  }
  if((x1==1 && y1==1) || (x2==1 && y2==1)) {
    int a=abs(x1-x2), b=abs(y1-y2);
    if(a==0 && b==3 && m==4) return 5;
    if(b==0 && a==3 && n==4) return 5;
    if(a==1 && b==1) return 4;
  }
  return knightdist_inf(x1,y1,x2,y2);
}

/**** Exemplo simples de uso ****/
#include <cstdio>

int main() {
  n = m = 4;

  //as coordenadas estão indexadas em 1
  printf("%d\n", knightdist(1,1, 3,3));
  printf("%d\n", knightdist(1,1, 4,1));

  return 0;
}
