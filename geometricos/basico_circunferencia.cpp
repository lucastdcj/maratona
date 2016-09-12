/*%
Algoritmos Básicos para Circunferência
Autor: Douglas Santos
Testes: poj-3831
Descricao: Calcula interseção entre duas circunferência,
e a aréa dessa intersecção.
Dependências: ccw
%*/

/**
Estrutura de ponto, circunferencia e reta aqui
**/

#include <cmath>
#include <algorithm>
#define F first
#define S second
using namespace std;

double sqr(double x) { return x*x; }

/* retorna 0, 1 ou 2 intersecções entre dois círculos e
 * se houver 1, em ia; se houver 2, em ia e ib */
int inter_circ(pt &ia, pt &ib, circ c1, circ c2) {
  int c = cmp(norma(c1.F-c2.F), c1.S+c2.S);
  if (c > 0) return 0;
  
  double dx=c2.F.x-c1.F.x;
  double dy=c2.F.y-c1.F.y;
  double d=sqr(dx)+sqr(dy);
  double r=sqrt((sqr(c1.S+c2.S)-d)*(d-sqr(c2.S-c1.S)));

  ia.x=ib.x=0.5*((c2.F.x+c1.F.x)+dx*(sqr(c1.S)-sqr(c2.S))/d);
  ia.y=ib.y=0.5*((c2.F.y+c1.F.y)+dy*(sqr(c1.S)-sqr(c2.S))/d);
  ia.x+=dy*r/(2*d); ib.x-=dy*r/(2*d);
  ia.y-=dx*r/(2*d); ib.y+=dx*r/(2*d);
  return 1-c;
}

/* Calcula a menor área quando o círculo é divido pela
corda dos pontos (a, b) */
double area_corda(circ c, pt a, pt b) {
  double d = norma(a - b);
  double r = c.S;
  double h = sqrt(r*r - (d*d)/4.0);
  double at = (d*h) / 2.0;
  double ang = 2 * acos(h / r);
  double ac = (ang * r * r) / 2.0;
  return ac - at;
}

/* Calcula a area da intersecção entre dois círculos */
double area_inter(circ c1, circ c2) {
  if (c1.S > c2.S) swap(c1, c2);
  c2.F.x = norma(c1.F - c2.F); c2.F.y = 0;
  c1.F.x = 0; c1.F.y = 0;
  pt ia, ib;
  int it = inter_circ(ia, ib, c1, c2);
  if (it == 1) return 0.0;
  if (it == 0) {
    if (cmp(c2.F.x, c1.S + c2.S) > 0) return 0.0;
    else return  pi * c1.S * c1.S;
  }
  
  double a1 = area_corda(c1, ia, ib);
  double a2 = area_corda(c2, ia, ib);
  if (ccw(ia, ib, c1.F) == ccw(ia, ib, c2.F)) {
    return a2 + pi * c1.S * c1.S - a1;
  }
  return a1 + a2;
}

/* Exemplo simples de uso */
int main() {
  circ c1, c2;
  pt ia, ib;
  int res;
  
  c1 = circ(pt(0, 0), 1);
  c2 = circ(pt(0, 2), 2);
  res = inter_circ(ia, ib, c1, c2);
  printf("%d (%lf %lf) (%lf %lf) %lf\n", res, ia.x, ia.y, 
         ib.x, ib.y, area_inter(c1, c2));
    
  return 0;
}

