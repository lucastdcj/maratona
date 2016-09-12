#include <cstdio>

#include <cstring>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

#define MAXN 100
#define INF 0x3f3f3f3f

int n, m;
int adj[MAXN][MAXN], peso[MAXN][MAXN], nadj[MAXN];

int d[MAXN][MAXN], p[2][MAXN], t[MAXN];

int mark[MAXN];

void mdst() {
  int i, j, k, u;

  // all-pairs-shortest-path
  for (k = 0; k < n; k++) {
    queue<int> Q;
    memset(mark, 0, sizeof(mark));
    d[k][k] = 0;
    mark[k] = 1;
    Q.push(k);
    while (!Q.empty()) {
      u = Q.front(); Q.pop();
      for (i = 0; i < nadj[u]; i++)
	if (!mark[adj[u][i]]) {
	  Q.push(adj[u][i]);
	  d[k][adj[u][i]] = d[k][u] + 1;
	  mark[adj[u][i]] = 1;
	}
    }
  }

}

int main() {
  int i, u, v;

  scanf("%d%d", &n, &m);
  for (i = 0; i < m; i++) {
    scanf("%d%d", &u, &v); u--; v--;
    adj[u][nadj[u]] = v; peso[u][nadj[u]++] = 1;
    adj[v][nadj[v]] = u; peso[v][nadj[v]++] = 1;
  }

  mdst();

  return 0;
}
