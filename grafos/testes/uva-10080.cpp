#include <stdio.h>
#include <math.h>

#include <cstring>

#include <cstring>
#include <vector>
using namespace std;
#define MAXN 212

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

typedef struct {double x, y;} point_t;

point_t gopher[MAXN];

double dis(point_t *a, point_t *b) {
  return sqrt((a->x-b->x)*(a->x-b->x) + (a->y-b->y)*(a->y-b->y));
}

#define eps 1e-9

int main() {
  int s, v;
  int nU, nV;
  while (scanf("%d%d%d%d", &nU, &nV, &s, &v) == 4) {
    int n = nU + nV;
    for (int i = 0; i < n; i++) adj[i].clear();
    for (int i = 0; i < nU; i++)
      scanf("%lf%lf", &gopher[i].x, &gopher[i].y);
    for (int i = 0; i < nV; i++) {
      point_t hole;
      scanf("%lf%lf", &hole.x, &hole.y);
      for (int j = 0; j < nU; j++)
	      if (dis(&hole, &gopher[j]) < v*s ||
	       fabs(v*s-dis(&hole, &gopher[j])) < eps) {
	        adj[j].push_back(i+nU);
	        adj[i+nU].push_back(j);
	      }
    }
    printf("%d\n", nU-maxbpm(n));
  }

  return 0;
}
