/*%
Verificações de Ponto em Polígono
Autor: Alexandre Kunieda (+ PUC-Rio + note da Mundial)
Complexidade: O(n), O(lg(n))
Tempo de implementacao: 1 minuto (cada)
Testes:
- inpoly(): uva.634
- inpoly_convex(): testes gerados na mão
Dependencias: 
- ccw()
- between3()
- intri() - soh inpoly_convex()
%*/

/**
Estrutura de ponto e poligono aqui
**/

int intri(pt k, pt a, pt b, pt c){
  int a1,a2,a3;

  a1 = ccw(a,k,b);
  a2 = ccw(b,k,c);
  a3 = ccw(c,k,a);

  if((a1*a2)>0 && (a2*a3)>0) return 1; /*dentro*/
  if(between3(k,a,b) || between3(k,b,c) || between3(k,c,a))
    return 2; /*borda*/
  return 0; /*fora*/
}

int inpoly(pt k, poly &p){
  int n = p.size();
  int cross = 0;

  for(int i=1; i<=n ; i++) {
    pt q=p[i-1], r=p[i%n];

    if( between3(k,q,r) ) return 2;
    if( q.y>r.y ) swap(q,r);
    if( q.y<k.y && r.y>=k.y  && ccw(k,q,r)>0 ) cross++;
  }

  return cross%2;
}

/* O(lg(n)) - só para polígonos convexos */
int inpoly_convex(pt k, poly& p){
  /* 'val' indica o sentido do polígono */
  int val = ccw(p[0],p[1],p[2]);
  /* tomar cuidado para o caso em que o polígono
     comeca com pontos colineares, 'val' receberá 0 */

  int esq,dir,meio, n = p.size();

  esq = 1; dir = n-1;
  while(dir>esq+1) {
    meio = (esq+dir)/2;

    if(ccw(p[0],p[meio],k) == val) esq = meio;
    else dir = meio;
  }

  return intri(k, p[0],p[esq],p[dir]);

  /* caso seja preciso verificar se está na borda,
   * substituir o return por:
   *
   * if(between3(k,p[esq],p[dir]) ||
   *    between3(k,p[0],p[1])     ||
   *    between3(k,p[0],p[n-1])) return 2;  //BORDA
   * return intri(k, p[0],p[esq],p[dir])?1:0;  //DENTRO:FORA
   */
}

/**** Exemplo simples de uso ****/
int main() {
  pt k;
  poly p;
  int n;
  int val;

  scanf(" %d", &n);
  while(n--) {
    scanf(" %lf %lf", &k.x,&k.y);
    p.push_back(k);
  }

  scanf(" %lf %lf", &k.x,&k.y);

  val = inpoly(k,p);
  /*val = inpoly_convex(k,p);*/
  printf("%d\n", val);

  return 0;
}
