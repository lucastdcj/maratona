/*%
Intersecção de Polígonos Convexos
Autor: PUC-Rio
Complexidade: O(n+m)
Tempo de implementacao: 8 min
Testes: uva.137
Dependencias:
- ccw()
- between3()
- intersect_seg()
- acha()
- inpoly()
Descricao: O algoritmo devolve a interseccao de dois poligonos
convexos, orientados em sentido anti-horario.
Pode ser utilizado inpoly_convex(), sem verificacao de ponto
na borda do poligono, ja que os poligonos sao convexos.
%*/

#define all(x) (x).begin(),(x).end()

/* os poligonos P e Q devem estar orientados em
   sentido anti-horario! */
poly poly_intersect(poly& P, poly& Q) {
  int m = Q.size(), n = P.size();
  int a = 0, b = 0, aa = 0, ba = 0, inflag = 0;
  poly R;
  while ((aa < n || ba < m) && aa < 2*n && ba < 2*m) {
    pt p1 = P[a], p2 = P[(a+1) % n], 
      q1 = Q[b], q2 = Q[(b+1) % m];
    pt A = p2 - p1, B = q2 - q1;
    int cross = cmp(A % B), ha = ccw(p2, q2, p1),
      hb = ccw(q2, p2, q1);
    if (cross == 0 && ccw(p1, q1, p2) == 0 && cmp(A*B) < 0) {
      if (between3(p1, q1, p2)) R.push_back(q1);
      if (between3(p1, q2, p2)) R.push_back(q2);
      if (between3(q1, p1, q2)) R.push_back(p1);
      if (between3(q1, p2, q2)) R.push_back(p2);
      if (R.size() < 2) return poly();
      inflag = 1; break;
    } else if (cross != 0 && intersect_seg(p1, p2, q1, q2)) {
      if (inflag == 0) aa = ba = 0;
      R.push_back(acha(p1, p2, q1, q2));
      inflag = (hb > 0) ? 1 : -1;
    }
    if (cross == 0 && hb < 0 && ha < 0) return R;
    bool t = cross == 0 && hb == 0 && ha == 0;
    if (t ? (inflag==1) : (cross>=0) ? (ha<=0) : (hb>0)) {
      if (inflag == -1) R.push_back(q2);
      ba++; b++; b %= m;
    } else {
      if (inflag == 1) R.push_back(p2);
      aa++; a++; a %= n;
    }
  }
  if (inflag == 0) {
    if (inpoly(P[0], Q)) return P;
    if (inpoly(Q[0], P)) return Q;
  }
  R.erase(unique(all(R)), R.end());
  if (R.size() > 1 && R.front() == R.back()) R.pop_back();
  return R;
}

/**** Exemplo simples de uso ****/
int main() {
  return 0;
}
