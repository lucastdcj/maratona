#include <vector>
#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;

typedef long long int int64;
long double eps=1e-8;
#define EPS 10e-9
#define REP(i,n) for(int i=0; i<(n); i++)

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

void init() {
  sa.clear();
  sx.clear();
}

void add(line r) {
  sa.insert(r);
  sx.insert(r);
}

void remove(line r) {
  sa.erase(r);
  sx.erase(r);
}

T getxMax(line r, line s) {
  return (s.b - r.b) / (r.a - s.a);
}

T gety(line r, T x) {
  return r.a * x + r.b;
}

T query(T x) {
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
int64 n, c, num;

struct El {
  int64 d, p, r, g;
  El() {};
  El(int64 d, int64 p, int64 r, int64 g) : d(d), p(p), r(r), g(g) {};
};

El v[100100];

bool comp(El a, El b) {
  return a.d < b.d;
}

int main()
{ 
  int cnt = 0;
  while (1) {
    scanf("%lld %lld %lld", &n, &c, &num);
    if (n == 0 && c == 0 && num == 0) return 0;
    REP(i, n) {
      int64 d, p, r, g;
      scanf("%lld %lld %lld %lld", &d, &p, &r, &g);
      v[i] = El(d, p, r, g);
    }
    init();
    sort(v, v+n, comp);
    insert(0, c);
    REP(i, n) {
      int64 y = query(v[i].d - 1);
      if (y < v[i].p) continue;
      y = y - v[i].p + v[i].r;
      int64 a, b;
      a = v[i].g;
      b = y - a * v[i].d;
      insert(a, b);
    }
    int64 y = query(num);
    printf("Case %d: %lld\n", ++cnt, y);
  }
  return 0;  
}
