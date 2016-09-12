#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

#define pb push_back
#define INF (0x3f3f3f3f)
typedef pair<int,int> ii;

#define MAXN 101

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
  int test = 0;
  while (scanf("%d",&n) == 1 && n) {
    test++;
    scanf("%d %d %d",&s,&t,&m);
    s--;t--;
    from.resize(m); to.resize(m); cap.resize(m); capr.resize(m);
    int u,v,c;
    int me = 0;
    for (int i = 0; i < m; i++) {
      scanf("%d %d %d",&u,&v,&c);
      u--;v--;
      from[me] = u; to[me] = v; cap[me] = c; capr[me++] = c;
    }
    printf("Network %d\n",test);
    printf("The bandwidth is %d.\n\n",maxflow());
  }
  return 0;
}
