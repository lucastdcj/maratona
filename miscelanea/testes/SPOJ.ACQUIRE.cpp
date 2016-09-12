#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
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
  if (sx.empty()) return INF;
  line r(-INF, -INF);
  r.xmax = x;
  it = sx.lower_bound(r);
  return -gety(*it, x);
}

bool insert(T a, T b) {
  a = -a;
  b = -b;
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

int main()
{
  int M,N,i;
  pair<int,int> a[50000];
  pair<int,int> rect[50000];
  scanf("%d",&M);
  for (i=0; i<M; i++)
    scanf("%d %d",&a[i].first,&a[i].second);
  sort(a,a+M);
  for (i=0,N=0; i<M; i++)
  {
    while (N>0&&rect[N-1].second<=a[i].second)
      N--;
    rect[N++]=a[i];
  }
  long long cost;
  insert(rect[0].second,0);

  for (i=0; i<N; i++)
  {
    cost=query(rect[i].first);
    if (i<N)
      insert(rect[i+1].second,cost);
  }
  printf("%lld\n",cost);
  return 0;
}