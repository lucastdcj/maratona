/* TLE no live archive (complexidade esperada n^2),
   mas passa nos casos testes oficiais */
#include <set>
#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long int int64;

#define EPS 10e-9
#define REP(i,n) for(int i=0; i<(n); i++)

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
  //printf("%lld %lld %lld\n", sa.begin()->a, sa.begin()->b, sa.begin()->xmax);
  if (sx.empty()) return INF;
  line r(-INF, -INF);
  r.xmax = x;
  it = sx.lower_bound(r);
  return -gety(*it, x);
}

bool insert(T a, T b) {
  a = -a;
  b = -b;
  // printf("INSERT %lld %lld\n", a, b);
   
  // printf("SA\n");
  // for (it = sa.begin(); it != sa.end(); it++) {
  //   printf("%lld %lld %lld\n", it->a, it->b, it->xmax);
  // }

  // printf("SX\n");
  // for (it = sx.begin(); it != sx.end(); it++) {
  //   printf("%lld %lld %lld\n", it->a, it->b, it->xmax);
  // }
  
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
  //printf("%lld %lld %lld\n", it->a, it->b, getxMax(r, *it));
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

int n, k;
T x[1020];
T w[1020];
T acw[1020];
T acwx[1020];
T memo[1020][1020];

int main()
{	
  while (scanf("%d %d", &n, &k) != EOF) {
    x[0] = 0;
    w[0] = 0;
    REP(i, n) {
      scanf("%lld %lld", &x[i+1], &w[i+1]);
    }
    n++;
    acw[0] = w[0];
    acwx[0] = w[0] * x[0];
    for (int i = 1; i < n; i++) {
      acw[i] = acw[i-1] + w[i];
      acwx[i] = acwx[i-1] + (w[i] * x[i]);
    }
    //memset(memo, 0x3f, sizeof(memo));
    for (int i = 0; i < n-1; i++) memo[i][0] = INF;
    for (int i = 0; i <= k; i++) memo[n-1][k] = INF;

    memo[n-1][0] = 0;
    for (int num = 1; num <= k; num++) {
      init();
      if (memo[n-1][num-1] != INF)
        insert(-x[n-1], memo[n-1][num-1] + x[n-1]*acw[n-1] - acwx[n-1]);
      //printf("%lld %lld\n", -x[n-1], memo[n-1][num-1] + x[n-1]*acw[n-1] - acwx[n-1]);
      for (int i = n-2; i >= 0; i--) {
        //printf("%lld %lld %lld\n", acw[i], acwx[i], query(acw[i]));
        memo[i][num] = query(acw[i]) + acwx[i];
        if (memo[i][num-1] != INF) {
          insert(-x[i], memo[i][num-1] + x[i]*acw[i] - acwx[i]);
        }
      }
    }
    printf("%lld\n", memo[0][k]);
  }
	return 0;
}