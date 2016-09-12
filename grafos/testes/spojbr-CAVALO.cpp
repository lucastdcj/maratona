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
  int k = 0;
  int nc, ns, na;
  while(scanf("%d %d %d",&nc,&ns,&na) == 3) {
    k++;
    printf ("Instancia %d\n",k);
    n = nc + ns + 2;
    m = na + ns + nc;
    from.resize(m); to.resize(m); cap.resize(m); capr.resize(m);
    s = 0;
    t = n-1;
    int me = 0;
    int c;
    for (int i = 1; i <= ns; i++) {
      from[me] = 0; to[me] = i; cap[me] = 1; capr[me++] = 0;
    }
    for (int i = ns+1; i < n-1; i++) {
      scanf("%d",&c);
      from[me] = i; to[me] = n-1; cap[me] =c; capr[me++] = 0;
    }
    int u,v;
    for (int i = 0; i < na; i++) {
      scanf("%d %d",&u,&v);
      u += ns;
      from[me] = v; to[me] = u; cap[me] = 1; capr[me++] = 0;
    }
    if (m != me) while(1);
    printf("%d\n\n",maxflow());
  }
  return 0;
}
