/*%
Diâmetro de Pontos e Polígono
Autor: Marcelo Póvoa
Complexidade: O(n) polígono convexo, O(n lg n) pontos
Testes: SPOJ.TFOSS (usar int64)
Dependencias: Graham (exceto para polígono convexo)
Descrição: Calcula a maior distância entre um par de pontos
de um polígono ou de um conjunto de pontos em posição geral
%*/
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int,int> pii;

int cmpa(poly &p, int i, int j) {
  int n = p.size();
  return cmp(triarea(p[i], p[(i+1) % n], p[(j+1) % n]),
    triarea(p[i], p[(i+1) % n], p[j]));
}

/* Retorna os O(n) pares de vértices de um polígono convexo
pelos quais passam um par de retas de suporte paralelas. O
polígono deve ser anti-horário e pode ter pontos colineares
*/
vector<pii> antipodals(poly &p) {
  int n = p.size();
  int i = n - 1, j;

  for (j = 0; cmpa(p, i, j) >= 0; j++) {}

  vector<pii> res(1, pii(i, j));
  int k = j;
  while (j) {
    i = (i+1) % n;
    res.push_back(pii(i, j));
    while (j && cmpa(p, i, j) >= 0) {
      j = (j+1) % n;
      if (i != k || j != 0)
        res.push_back(pii(i, j));
    }
    if (!cmpa(p, i, j) && (i != k || j != n-1))
      res.push_back(pii(i, (j+1) % n));
  }
  return res;
}

double diam_convex(poly p) { // p em sentido horário
  double res = 0;
  reverse(p.begin(),p.end());

  vector<pii> c = antipodals(p);
  for (int i = 0; i < c.size(); i++)
    res = max(res, norma(p[c[i].first]-p[c[i].second]));

  return res;
}

double diam_points(poly &p) {
  if (p.size() <= 1) return 0;
  if (p.size() == 2) return norma(p[0] - p[1]);
  return diam_convex(graham(p));
}

/**** Exemplo simples de uso ****/
int main() {
  int n;
  poly p;
  pt k;
  
  scanf(" %d", &n);
  while(n--) {
    scanf(" %lf %lf", &k.x, &k.y);
    p.push_back(k);
  }

  printf("%.2lf\n", diam_convex(p));
  return 0;
}
