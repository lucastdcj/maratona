/*%
Convex Hull (Graham Scan)
Autor: Alexandre Kunieda (+ PUC-Rio)
Complexidade: O(n*lg(n))
Testes: uva.218, uva.596, uva.10065, uva.11096, nuevo.3655
Dependencias: 
- norma()
- ccw()
Descricao: Algoritmo de Graham, para obter o Convex Hull de um
dado conjunto de pontos
%*/

/**
Estrutura de ponto e poligono aqui
**/

pt pivo;
/* ordena em sentido horario */
bool cmp_radial(pt a, pt b){ 
  int aux = ccw(pivo, a,b);
  return ((aux<0) || (aux==0 && norma(a-pivo)<norma(b-pivo)));
}
bool cmp_pivo(pt p, pt q){ /* pega o de menor x e y */
  int aux = cmp( p.x, q.x );
  return ((aux<0) || (aux==0 && cmp( p.y, q.y )<0));
}
/* usar poly& p reduz tempo, mas desordena o conj de pontos */
poly graham(poly p){
  int i,j,n = p.size();
  poly g;

  /* ordena e torna o conj de pontos um poligono estrelado */
  pivo = *min_element(p.begin(), p.end(), cmp_pivo);
  sort(p.begin(), p.end(), cmp_radial);

  /* para pegar colineares do final do poligono
   *
   * for(i=n-2 ; i>=0 && ccw(p[0], p[i], p[n-1])==0 ; i--);
   * reverse(p.begin()+i+1, p.end());
   */

  for(i=j=0 ; i<n ; i++) {
    /* trocar ccw>=0 por ccw>0 para pegar colineares */
    while( j>=2 && ccw(g[j-2], g[j-1], p[i]) >= 0 ){
      g.pop_back(); j--;
    }
    g.push_back(p[i]); j++;
  }

  return g;
}

/**** Exemplo simples de uso ****/
int main() {
  int i,n;
  poly p;
  pt k;

  scanf(" %d", &n);
  while(n--){
    scanf(" %lf %lf", &k.x, &k.y);
    p.push_back(k);
  }

  poly g = graham(p);

  for(i=0 ; i<g.size() ; i++)
    printf("(%lf,%lf)\n", g[i].x, g[i].y);

  return 0;
}
