#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

#define MAXN 20100
#define pb push_back

int nadj[MAXN];
vector<int> adj[MAXN];
int comp[MAXN], vis[MAXN], stck[MAXN], t, high[MAXN], num, ncomp;

void dfscc(int u) {
  int i, v;
  high[u] = vis[u] = num--;
  stck[t++] = u;
  for (i = 0; i < nadj[u]; i++) {
    v = adj[u][i];
    if (!vis[v]) {
      dfscc(v);
      high[u] = max(high[u], high[v]);
    } else if (vis[v] > vis[u] && !comp[v])
      high[u] = max(high[u], vis[v]);
  }
  if (high[u] == vis[u]) {
    ncomp++;
    do {
      v = stck[--t];
      comp[v] = ncomp;
    } while (v != u);
  }
}

void scc(int n) {
  int i;
  ncomp = t = 0; num = n;
  memset(vis, 0, sizeof(vis));
  memset(comp, 0, sizeof(comp));
  for (i = 0; i < n; i++)
    if (!vis[i])
      dfscc(i);
}

/*n deve ser o numero total de verties (2*p))*/
bool two_sat(int n) {
  bool ok = true;
  int i;
  scc(n);
  for (i=0; i<n/2 && ok; i++)
    ok &= (comp[2*i] != comp[2*i+1]);
  return ok;
}

#define N(x) (2*x + 1)
#define Y(x) (2*x)
#define NEG(x) (x%2 == 1 ? x-1 : x+1)

void clau(int x, int y) {
  int negx = NEG(x);
  int negy = NEG(y);
  adj[negx].pb(y);
  adj[negy].pb(x);
}

int main() {
  int c,p;
  while (scanf("%d %d",&c,&p) == 2 && (c || p)) {
    memset(nadj,0,sizeof(nadj));
    for (int i = 0; i < 2*p + 1; i++) adj[i].clear();
    for (int i = 0; i < c; i++) {
      int x, y, s, t;
      scanf("%d %d %d %d",&x,&y,&s,&t);
      x--;y--;s--;t--;
      if (x == -1) swap(x,y);
      if (y == -1) y = x;
      if (x != -1) clau(Y(x),Y(y));
      if (s == -1) swap(t,s);
      if (t == -1) t = s;
      if (s != -1) clau(N(t),N(s));
    }
    for (int i = 0; i < 2*p + 1; i++) nadj[i] = adj[i].size();
    if (two_sat(2*p)) printf("yes\n");
    else printf("no\n");      
  }
  return 0;
}
