/*%
Algoritmos de Intersecções
Autor: Alexandre Kunieda + (PUC-Rio)
Testes: 
- UVa 11068 [intersect] [acha] t=0.010s
- UVa 866 [intersect_seg] [intersect_seg_2] [acha] t=0.000s
- UVa 378 [intersect] [acha] t=0.010s
- UVa 191 [intersect_seg] [intersect_seg_2] t=0.000s
- POJ 3819 [inter_reta_circ]
Dependências: 
- comparacoes na estrutura de ponto - soh intersect_seg()
- norma() - distPR(), inter_reta_circ()
- projecao() - distPR(), inter_reta_circ()
- between3() - distPR(), intersect_seg_2(), inter_reta_circ()
- ccw() - soh intersect_seg_2()
Descricao: Determina se há intersecção ou o ponto de
intersecção entre segmentos de reta ou retas. Acha inter-
secções entre segmento de reta ou reta e circunferência.
Também contém função que devolve a distância de um ponto
a uma reta.
%*/

/**
Estruturas aqui
**/

int intersect(reta p0, reta q0){ /*intersecção de retas*/
  eq_reta p(p0), q(q0);

  if(cmp(p.A*q.B , p.B*q.A)==0){ /*paralelos*/
    if(cmp(p.A*q.C , p.C*q.A)==0 &&
       cmp(p.B*q.C , p.C*q.B)==0) return 2; /*reta*/
    else return 0; /*nada*/
  }
  return 1; /*ponto*/
}

/* intersecção nos extremos dos segmentos tbm é contada! */
bool intersect_seg(pt p, pt q, pt r, pt s) {
  pt A = q - p, B = s - r, C = r - p, D = s - q;
  int a = cmp(A % C) + 2 * cmp(A % D);
  int b = cmp(B % C) + 2 * cmp(B % D);
  if (a == 3 || a == -3 || b == 3 || b == -3) return false;
  if (a || b || p==r || p==s || q==r || q==s) return true;
  int t = (p < r) + (p < s) + (q < r) + (q < s);
  return t != 0 && t != 4;
}

bool intersect_seg_2(pt p, pt q, pt r, pt s) {
  int a = ccw(p,q,r)*ccw(p,q,s);
  int b = ccw(r,s,p)*ccw(r,s,q);

  if(a<0 && b<0) return true;
  else return false;

  // tire o 'else' para verificar intersecção nos extremos
  if(a>0 || b>0) return false;

  return ( between3(p,r,s) ||
           between3(q,r,s) ||
           between3(r,p,q) ||
           between3(s,p,q) );
}

/*acha intersecção de duas retas*/
pt acha(pt a, pt b, pt c, pt d){
  /* pressupoe que haja intersecção! */
  eq_reta p(reta(a,b)), q(reta(c,d)); 
  pt k;

  k.x = (q.C*p.B - p.C*q.B)/(p.A*q.B - q.A*p.B);
  k.y = (q.C*p.A - p.C*q.A)/(p.B*q.A - q.B*p.A);
  return k;
}

/*acha intersecção de duas retas - da PUC*/
pt acha_(pt p, pt q, pt r, pt s){
  pt a = q-p, b = s-r, c = pt(p%q,r%s);
  return pt(pt(a.x, b.x)%c, pt(a.y, b.y)%c) / (a%b);
}

/* distância de um ponto a uma reta */
double distPR(pt p, reta r){
  pt v = p - r.ini;
  pt w = r.fim - r.ini;

  pt proj = projecao(v,w);
  /* (proj+r.ini) é o ponto mais proximo de p,
     e que pertence à reta r */

  /* para segmentos de reta
   *
   * if( !between3(proj+r.ini, r.ini, r.fim) ) 
   *   return min( norma(p-r.ini), norma(p-r.fim) );
   */

  return norma(v - proj);
}

/* retorna 0, 1 ou 2 intersecções entre segmento/reta e
 * círculo: se houver 1, em ia; se houver 2, em ia e ib */
int inter_reta_circ(pt &ia, pt &ib, reta r, circ c) {
  pt p = r.ini + projecao(c.first - r.ini, r.fim - r.ini);
  double d = norma(p - c.first);

  if (cmp(d, c.second) > 0) return 0;

  pt v = cmp(norma(r.ini - p)) ? r.ini : r.fim;
  v = versor(v - p) * sqrt(max(0.0,c.second*c.second - d*d));

  ia = p + v; ib = p - v;

  /* para segmentos de reta, descomente
   * int ba = between3(ia, r.ini, r.fim);
   * int bb = between3(ib, r.ini, r.fim);
   * if (!ba) {
   *   ia = ib;
   *   return bb;
   * }
   */ 
  return (cmp(norma(ia - ib))/* && bb*/) + 1;
}

/**** Exemplo simples de uso ****/
int main(){
  /**** Especifico do problema UVa 378 ****/
  int n, i,aux;
  reta r[2];
  pt p;

  puts("INTERSECTING LINES OUTPUT");

  scanf(" %d", &n);
  while(n--){
    for(i=0 ; i<2 ; i++)
      scanf(" %lf %lf %lf %lf",
            &r[i].ini.x, &r[i].ini.y,
            &r[i].fim.x, &r[i].fim.y);

    aux = intersect(r[0], r[1]);

    if(aux == 0) puts("NONE");
    if(aux == 1){
      p = acha(r[0].ini,r[0].fim, r[1].ini,r[1].fim);
      printf("POINT %.2lf %.2lf\n", p.x,p.y);
    }
    if(aux == 2) puts("LINE");
  }

  puts("END OF OUTPUT");

  return 0;
}
