/*%
Par de Pontos Mais Próximos
Autor: Notebook Unicamp (Mundial)
Complexidade: O(n*lg(n))
Tempo de implementacao: 2 minutos
Testes: 
- UVa 10245 (n<=10000) t=0.290s
Dependencias: 
- norma()
Descricao: Obtem a menor distancia entre pontos de um conjunto
de pontos. Eh preciso que o conjunto contenha pelo menos 2
pontos para o algoritmo funcionar
%*/

#include <set>
#define foreach(it, a,b) for(typeof(a)it=(a) ; it!=(b) ; it++)
#define all(x) (x).begin(), (x).end()

bool ycmp(pt a, pt b) {
  if (a.y!=b.y) return a.y<b.y;
  return a.x<b.x;
}
double closest_pair (poly &P) {
  int n = P.size();
  double d = norma(P[0]-P[1]);
  set<pt, bool(*)(pt,pt)> s(&ycmp);

  sort(all(P));
  for(int i=0,j=0 ; i<n ; i++) {
    pt lower(0, P[i].y - d) , upper(0, P[i].y + d);
    while(P[i].x - P[j].x > d)
      s.erase(P[j++]);

    foreach(p, s.lower_bound(lower), s.upper_bound(upper))
      /* os pontos mais proximos sao tirados de P[i] e *p */
      d = min(d, norma(P[i] - *p));
    s.insert(P[i]);
  }
  return d;
}

/**** Exemplo simples de uso ****/
int main(){
  /**** especifico para o problema UVa 10245 ****/
  pt i;
  poly p;
  int k,n;
  double d;

  while(scanf(" %d", &n)==1 && n) {
    p.clear();

    for(k=0 ; k<n ; k++) {
      scanf(" %lf %lf", &i.x,&i.y);
      p.push_back(i);
    }

    if(n==1) d = 15000.0;
    else d = closest_pair(p);

    if(d>10000) puts("INFINITY");
    else printf("%.4lf\n", d);
  }

  return 0;
}
