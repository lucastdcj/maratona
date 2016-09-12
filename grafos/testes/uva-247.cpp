#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

#define MAXN 100

int n, m;
int adj[MAXN][MAXN], nadj[MAXN];
int comp[MAXN], vis[MAXN], stck[MAXN], t, high[MAXN], num, ncomp;

char name[MAXN][30];
map<string, int> dict;

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

void scc() {
  int i;
  ncomp = t = 0; num = n;
  memset(vis, 0, sizeof(vis));
  memset(comp, 0, sizeof(comp));
  for (i = 0; i < n; i++)
    if (!vis[i])
      dfscc(i);
}

int A[MAXN][MAXN];

int find(char *u) {
  string s(u);
  if (dict.find(s) == dict.end()) {
    dict[s] = n;
    strcpy(name[n++], u);
  }
  return dict[s];
}

int main() {
  int i, j, cases = 1;
  int first = 1;

  for (;;) {
    scanf("%d%d", &n, &m);
    if (!n && !m) break;
    dict.clear();
    memset(A, 0, sizeof(A)); n = 0;
    for (i = 0; i < m; i++) {
      int u, v;
      char n1[30], n2[30];
      scanf(" %s %s", n1, n2); 
      u = find(n1); v = find(n2);
      A[u][v] = 1;
    }
    memset(nadj, 0, sizeof(nadj));
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
	if (A[i][j])
	  adj[i][nadj[i]++] = j;
    scc();

    if (!first) printf("\n"); first = 0;
    printf("Calling circles for data set %d:\n", cases++);
    for (i = 1; i <= ncomp; i++) {
      int first = 1;
      for (j = 0; j < n; j++) if (comp[j] == i) {
	  if (!first) printf(", "); first = 0;
	  printf("%s", name[j]);
	}
      printf("\n");
    }
  }

  return 0;
}


