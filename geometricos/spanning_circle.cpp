/*%
Círculo Gerador Mínimo
Autor: PUC-Rio
Complexidade: O(n^3)
Tempo de implementacao: 3 min
Testes:
- SPOJbr ICPC (n<=100) t=0.35s
- UVa 10005 (n<=100) t=0.002s
Dependencias:
- norma()
Descricao: O algoritmo devolve o circulo de raio minimo que
contem todos os pontos dados
%*/

bool in_circle(circ C, pt p){
  return cmp(norma(p - C.first), C.second) <= 0;
}

pt circumcenter(pt p, pt q, pt r) {
  pt a = p - r, b = q - r,
    c = pt(a * (p + r) / 2, b * (q + r) / 2);

  return pt(c % pt(a.y, b.y),pt(a.x, b.x)%c) / (a%b);
}

circ spanning_circle(vector<pt>& T) {
  int n = T.size();

  circ C(pt(), -INFINITY);
  for (int i = 0; i < n; i++) if (!in_circle(C, T[i])) {
    C = circ(T[i], 0);
    for (int j = 0; j < i; j++) if (!in_circle(C, T[j])) {
      C = circ((T[i] + T[j]) / 2, norma(T[i] - T[j]) / 2);
      for (int k = 0; k < j; k++) if (!in_circle(C, T[k])) {
        pt o = circumcenter(T[i], T[j], T[k]);
        C = circ(o, norma(o - T[k]));
      }
    }
  }

  return C;
}
