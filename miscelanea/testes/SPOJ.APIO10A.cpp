/* TLE no spoj (complexidade esperada n),
   mas passa nos casos testes oficiais */
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
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
  if (sx.empty()) return -INF;
  line r(-INF, -INF);
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

const int MAXN = 1000001;
int N , a , b , c;
int x[MAXN];
long long sum[MAXN];
long long dp[MAXN];

int main(){

        scanf("%d" , &N);
        scanf("%d %d %d" , &a , &b , &c);
        init();
        for(int n = 1 ; n <= N ; n++){
                scanf("%d" , &x[n]);
                sum[n] = sum[n - 1] + x[n];
        }
        dp[1] = a * x[1] * x[1] + b * x[1] + c;
        insert(-2 * a * x[1] , dp[1] + a * x[1] * x[1] - b * x[1]);
 
        for(int n = 2 ; n <= N ; n++){
                dp[n] = a * sum[n] * sum[n] + b * sum[n] + c;
                dp[n] = max(dp[n] , b * sum[n] + a * sum[n] * sum[n] + c + query(sum[n]));
                insert(-2 * a * sum[n] , dp[n] + a * sum[n] * sum[n] - b * sum[n]);
        }
        printf("%lld\n", dp[N]);
    
    return 0;
}