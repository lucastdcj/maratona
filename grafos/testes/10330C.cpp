#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

#define pb push_back
#define INF (0x3f3f3f3f)
typedef pair<int,int> ii;

#define MAXN 300

vector<int> adj[MAXN], from, to, x, cap, capr;
int nadj[MAXN], pai[MAXN], paie[MAXN];

int s; int t;
int n,m;

int aumenta() {
  queue<ii> q;
  int u,v,e,f;
  ii a;
  memset(pai,-1,sizeof(pai));
  pai[s] = s;
  q.push(ii(s,INF));
  while(!q.empty()) {
    a = q.front(); q.pop();
    v = a.first; f = a.second;
    if (v == t) break;
    for (int i = 0; i < nadj[v]; i++) {
      e = adj[v][i];
      if (from[e] == v) { 
	u = to[e];
	if (pai[u] != -1 || x[e] == cap[e]) continue;
	q.push(ii(u,min(f,cap[e] - x[e])));
      }
      else {
	u = from[e];
	if (pai[u] != -1 || x[e] == -capr[e]) continue;
	q.push(ii(u,min(f,capr[e] + x[e])));
      }
      pai[u] = v; paie[u] = e;
    }
  }
  if (v != t) return 0;
  while (v != s) {
    e = paie[v];
    if (to[e] == v) x[e] += f;
    else x[e] -= f;
    v = pai[v];
  }
  return f;
}

int maxflow() {
  x.resize(m); fill(x.begin(),x.end(),0);
  for (int i = 0; i < n; i++) adj[i].clear();
  for (int i = 0; i < m; i++) 
    adj[from[i]].pb(i), adj[to[i]].pb(i);
  for (int i = 0; i < n; i++) nadj[i] = adj[i].size();
  int f,r=0;
  while((f = aumenta())) r += f;
  return r;
}

int main() {
  int i;
  int b, d, u, v, c;

  while (scanf("%d", &n) == 1) {
    if (!n) break;
    from.clear(); to.clear(); cap.clear(); capr.clear();
    for (i = 1; i <= n; i++) {
      scanf("%d", &c);
      from.pb(2*i-1); to.pb(2*i); cap.pb(c); capr.pb(0);
    }
    scanf("%d", &m);
    for (i = 0; i < m; i++) {
      scanf("%d%d%d", &u, &v, &c);
      from.pb(2*u); to.pb(2*v-1); cap.pb(c); capr.pb(0);
    }
    s = 0;
    t = 2*n+1;
    n = 2*n+2;
    scanf("%d%d", &b, &d);
    for (i = 0; i < b; i++) {
      scanf("%d", &u);
      from.pb(s); to.pb(2*u-1); cap.pb(INF); capr.pb(0);
    }
    for (i = 0; i < d; i++) {
      scanf("%d", &u);
      from.pb(2*u); to.pb(t); cap.pb(INF); capr.pb(0);
    }
    m = from.size();
    printf("%d\n", maxflow());
  }
  
  return 0;
}
