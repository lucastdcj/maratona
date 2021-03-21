/*%
Estrutura e Base para Geométricos
Autor: Alexandre Kunieda (+ PUC-Rio)
Tempo de implementacao: 5 minutos
Descricao: Contem estrutura de ponto, reta, poligono e algumas
operacoes-base para os algoritmos geometricos
%*/

#include <cmath>
#include <vector>

using namespace std;

const double pi = acos(-1);

int cmp(double a, double b = 0) {
  if (fabs(a - b) < 1e-8) return 0;
  if (a < b) return -1;
  return 1;
}

struct pt {
  double x, y;
  explicit pt(double x = 0, double y = 0) : x(x), y(y) {}

  pt operator+(pt q) { return pt(x + q.x, y + q.y); }
  pt operator-(pt q) { return pt(x - q.x, y - q.y); }
  pt operator*(double t) { return pt(x * t, y * t); }
  pt operator/(double t) { return pt(x / t, y / t); }
  double operator*(pt q) { return x * q.x + y * q.y; }
  double operator%(pt q) { return x * q.y - y * q.x; }

  int cmp(pt q) const {
    if (int t = ::cmp(x, q.x)) return t;
    return ::cmp(y, q.y);
  }
  bool operator==(pt q) const { return cmp(q) == 0; }
  bool operator!=(pt q) const { return cmp(q) != 0; }
  bool operator<(pt q) const { return cmp(q) < 0; }
};

struct reta {
  pt ini, fim;
  reta() {}
  reta(pt ini, pt fim) : ini(ini), fim(fim) {}
};

struct eq_reta {
  double A, B, C; /* Ax + By + C = 0 */

  void init(reta p) {
    pt aux = p.ini - p.fim;
    A = aux.y;
    B = -aux.x;
    C = -A * p.ini.x - B * p.ini.y;
  }
  eq_reta(reta p) { init(p); }
};

typedef vector<pt> poly;
typedef pair<pt, double> circ;

pt normal(pt v) { return pt(-v.y, v.x); }
double norma(pt v) { return hypot(v.x, v.y); }
pt versor(pt v) { return v / norma(v); }
double anglex(pt v) { return atan2(v.y, v.x); }
double angle(pt v1, pt v2) { /* angulo orientado ccw */
  return atan2(v1 % v2, v1 * v2);
}
double triarea(pt a, pt b, pt c) {  /* area c/ sinal */
  return ((b - a) % (c - a)) / 2.0; /* area>0 = ccw ; area<0 = cw */
}
int ccw(pt a, pt b, pt c) {      /* b-a em relacao a c-a */
  return cmp((b - a) % (c - a)); /* ccw=1 ; cw=-1 ; colinear=0 */
  /* equivalente a cmp(triarea(a,b,c)), mas evita divisao */
}
pt projecao(pt v, pt w) { /* proj de v em w */
  double alfa = (v * w) / (w * w);
  return w * alfa;
}
