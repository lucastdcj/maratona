/*%
Funções para Datas
Autor: Alexandre Kunieda/Marcelo Póvoa
Complexidade: O(1)
Testes: uva.602/nuevo.4306

Zeller: Eh capaz de calcular o dia da semana para o calendario
gregoriano (atual) - chame zeller() -, ou calendario juliano
(antigo, considerava bissexto todo ano multiplo de 4, sem as
regras de multiplo de 100 e 400) - chame zeller_julian().
Getdate: Retorna o numero de dias a partir do ano 0 ate a data
%*/

bool bissex(int y) { return (y%4==0 && (y%100 || y%400==0)); }

int zeller(int d, int m, int y) {
  if(m<3) --y, m+=12;
  return (d + ((m+1)*13)/5 + y + y/4 +
          6*(y/100) + y/400 + 6) % 7;
}

int zeller_julian(int d, int m, int y) {
  if(m<3) --y, m+=12;
  return (d + ((m+1)*13)/5 + y + y/4 + 4) % 7;
}

int getdate(int d, int m, int y) { //mes e dia a partir de 1
  int qm[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
  int s=0;
  for (int i=1; i<m; i++) s+=qm[i];

  int res=365*y+s+d+(y/4-y/100+y/400);
  if (m<3 && bissex(y)) res--;
  return res;
}

/**** Exemplo simples de uso ****/
#include <cstdio>

char wkday[]="DSTQQSS";

int main() {
  int d,m,y;

  while(scanf(" %d %d %d", &d, &m, &y)==3) {
    printf("%d/%d/%d is a %c\n", d,m,y,wkday[zeller(d,m,y)]);
    printf("%d/%d/%d = %d days\n", d,m,y,getdate(d,m,y));
  }

  return 0;
}
