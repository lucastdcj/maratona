#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m;

// Maximum number of vertices in the graph
#define MAXN 212

// Maximum edge weight (MAXW * NN * NN must fit into an int)
#define MAXW 1000

// Adjacency matrix and some internal arrays
int g[MAXN][MAXN], v[MAXN], w[MAXN], na[MAXN];
bool a[MAXN];

int mincut(int n) {
  // init the remaining vertex set
  for(int i = 0; i < n; i++) v[i] = i;

  // run Stoer-Wagner
  int best = MAXW * n * n;
  while(n > 1) {
    // initialize the set A and vertex weights
    a[v[0]] = true;
    for( int i = 1; i < n; i++ ) {
      a[v[i]] = false;
      na[i - 1] = i;
      w[i] = g[v[0]][v[i]];
    }

    // add the other vertices
    int prev = v[0];
    for(int i = 1; i < n; i++) {
      // find the most tightly connected non-A vertex
      int zj = -1;
      for(int j = 1; j < n; j++)
	if(!a[v[j]] && (zj < 0 || w[j] > w[zj]))
	  zj = j;

      // add it to A
      a[v[zj]] = true;

      // last vertex?
      if(i == n - 1) {
	// remember the cut weight
	best = min(best, w[zj]);

	// merge prev and v[zj]
	for(int j = 0; j < n; j++)
	  g[v[j]][prev] = g[prev][v[j]] += g[v[zj]][v[j]];
	v[zj] = v[--n];
	break;
      }
      prev = v[zj];

      // update the weights of its neighbours
      for(int j = 1; j < n; j++)
	if(!a[v[j]])
	  w[j] += g[v[zj]][v[j]];
    }
  }
  return best;
}

int main() {
  int t, i, u, v, c;
  int cases = 1;

  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &m);
    memset(g, 0, sizeof(g));
    for (i = 0; i < m; i++) {
      scanf("%d%d%d", &u, &v, &c); u--; v--;
      g[u][v] = g[v][u] = c;
    }
    printf("Case #%d: %d\n", cases++, mincut(n));
  }

  return 0;
}
