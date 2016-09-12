/*%
  Convex Hull Trick
  Autor: Douglas Oliveira Santos
  Complexidade: O(lg n) - insert e query
  Testes: LA5133, LA6131, SPOJ.ACQUIRE, SPOJ.APIO10A
  Descrição: Estrutura de dados que permite inserir retas
  não-verticais na forma y(x)=A*x+B e consultar, dado x*,
  qual é o maior y(x*) entre as retas existentes. Para se
  obter o menor no lugar do maior, troque os sinais de A,
  B e do resultado da query.
  Funciona para int e double.
  %*/
 
#include <set>
#include <algorithm>
#include <cmath>
using namespace std;

// Caso queira double, troque as 2 linhas abaixo
typedef long long int T;
#define INF 0x3f3f3f3f3f3f3f3fLL

struct line {
  T a, b, xmax;
  line(T a, T b) : a(a), b(b) {};
};

bool compa(line a, line b) {
  return a.a < b.a;
}

bool compx(line a, line b) {
  return a.xmax < b.xmax;
}

bool(*fcompa)(line,line) = compa;
bool(*fcompx)(line,line) = compx;

set<line, bool(*)(line, line)> sa(fcompa); 
set<line, bool(*)(line, line)> sx(fcompx); 

set<line, bool(*)(line, line)>::iterator it;

/* Funcao auxiliar */
void add(line r) {
  sa.insert(r);
  sx.insert(r);
}

/* Funcao auxiliar */
void remove(line r) {
  sa.erase(r);
  sx.erase(r);
}

/* Funcao auxiliar */
T getxMax(line r, line s) {
   //return (s.b - r.b) / (r.a - s.a); // para double
  return floor((double) (s.b - r.b) / (double) (r.a - s.a));
}

/* Funcao auxiliar */
T gety(line r, T x) {
  return r.a * x + r.b;
}

void init() {
  sa.clear();
  sx.clear();
}

T query(T x) {
  if (sx.empty()) return -INF;
  line r(0, 0);
  r.xmax = x;
  it = sx.lower_bound(r);
  return gety(*it, x);
}

bool insert(T a, T b) {
  line r(a, b);
  it = sa.lower_bound(r);
  if (it != sa.end() && it->a == r.a) {
    if (it->b >= r.b) return false;
    remove(*it);
  }
  it = sa.lower_bound(r);
  if (it != sa.end() && it != sa.begin()) {
    line s = *it;
    it--;
    if (getxMax(r, s) <= getxMax(r, *it)) return false;
  }
  while (1) {
    it = sa.lower_bound(r);
    if (it == sa.end()) break;
    if (getxMax(r, *it) >= it->xmax) {
      remove(*it);
    }
    else {
      break;
    }
  }
  while (1) {
    it = sa.lower_bound(r);
    if (it == sa.begin()) break;
    it--;
    line s = *it;
    if (it == sa.begin()) {
      remove(s);
      s.xmax = getxMax(s, r);
      add(s);
      break;
    }
    it--;
    line t = *it;
    remove(s);
    if (getxMax(s, r) > t.xmax) {
      s.xmax = getxMax(s, r);
      add(s);
      break;
    }
  }
  it = sa.lower_bound(r);
  if (it == sa.end()) r.xmax = INF;
  else r.xmax = getxMax(r, *it);
  add(r);
  return true;
}

/**** Exemplo simples de uso ****/
int main() {
  init();
  insert(0, -10);
  insert(-2, -0);
  insert(-1,-7);
  insert(-2,-3);
  insert(-2, -2);
  printf("%lld\n",query(5));
  return 0;
}
