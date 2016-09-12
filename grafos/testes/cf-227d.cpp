#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <cctype>
#include <stack>
using namespace std;

typedef long long int int64;

#define EPS 10e-9
#define INF 0x3f3f3f3f
#define REP(i,n) for(int i=0; i<(n); i++)

#define MAXN 1020

/* Input - FILL ME */
vector<int> adj[MAXN];
/* Output */
int conj[MAXN]; // conj[u] = v, se v for emparelhado com u
int cor[MAXN];  // cor[u] = partição do vertice u (0 ou 1)
/* Variavel auxiliar */
int vis[MAXN];

/* Função auxiliar */
bool DFS(int u, int c) {
  cor[u] = c;
  for (int i = 0; i < (int) adj[u].size(); i++) {
    int v = adj[u][i];
    if (cor[v] == c) return false;
    if (cor[v] == -1) {
      if (!DFS(v, c^1)) return false;
    }
  }
  return true;
}

/* Função auxiliar */
int aumenta(int u) {
  int i;
  for (i = 0; i < (int) adj[u].size(); i++) {
    int v = adj[u][i];
    if (vis[v]) continue; vis[v] = 1;
    if (conj[v] == -1 || aumenta(conj[v])) {
      conj[v] = u;
      conj[u] = v;
      return 1;
    }
  }
  return 0;
}

int maxbpm(int n) {
  int i;
  int res = 0;
  memset(cor, -1, sizeof(cor));
  for (int i = 0; i < n; i++) {
    if (cor[i] == -1) 
      if (!DFS(i, 0)) return -1; // grafo não é bipartido
  }
  memset(conj, -1, sizeof(conj));
  for (i = 0; i < n; i++) {
    if (cor[i]) continue;
    memset(vis, 0, sizeof(vis));
    if (aumenta(i)) res++;
  }
  return res;
}

int ed[1020][2];

int main()
{	
  int n, m;
  while(scanf("%d %d", &n, &m) != EOF) {
    REP(i, m) {
      int u, v;
      scanf("%d %d", &u, &v);
      u--; v--;
      ed[i][0] = u;
      ed[i][1] = v;
    }
    int res = INF;
    REP(i, n) {
      int num = 0;
      int sum = 0;
      REP(j, 2*n) adj[j].clear();
      int tot = 0;
      REP(j, m) {
        int u = ed[j][0];
        int v = ed[j][1];
        if (u == i || v == i) num++;
        else {
          adj[u].push_back(n+v);
          adj[n+v].push_back(u);
          tot++;
        }
      }
      sum += 2*n - 1 - num;
      //printf("%d %d %d\n", i, num, sum);
      int mb = maxbpm(2*n);
      //printf("%d %d\n", tot, mb);
      sum += (tot - mb);
      sum += (n-1 - mb);
      res = min(res, sum);
    }
    printf("%d\n", res);
  }
	return 0;
}