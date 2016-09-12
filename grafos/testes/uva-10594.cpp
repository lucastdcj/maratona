#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm> 

using namespace std;

// the maximum number of vertices + 1
#define MAXN 1024

// adjacency matrix (fill this up)
int cap[MAXN][MAXN];

// cost per unit of flow matrix (fill this up)
long long cost[MAXN][MAXN];

// flow network and adjacency list
int n, m, s, t;
int x[MAXN][MAXN], A[MAXN][MAXN], nadj[MAXN];

// Dijkstra's successor and depth
int par[MAXN];
long long d[MAXN];        // par[source] = source;

// Labelling function
long long pi[MAXN];

#define INF (0x3f3f3f3f3f3f3f3fll)

// Dijkstra's using non-negative edge weights (cost + potential)
#define Pot(u,v) (d[u] + pi[u] - pi[v])

bool dijkstra( int n, int s, int t ) {
  for( int i = 0; i < n; i++ ) d[i] = INF, par[i] = -1;
  d[s] = 0;
  par[s] = -n - 1;

  for (;;) {
    // find u with smallest d[u]
    int u = -1; long long bestD = INF;
    for(int i = 0; i < n; i++) if (par[i] < 0 && d[i] < bestD)
				 bestD = d[u = i];
    if(bestD == INF) break;

    // relax edge (u,i) or (i,u) for all i;
    par[u] = -par[u] - 1;
    for (int i = 0; i < nadj[u]; i++)
      {
	// try undoing edge v->u      
	int v = A[u][i];
	if (par[v] >= 0 ) continue;
	if (x[v][u] && d[v] > Pot(u,v) - cost[v][u]) 
	  d[v] = Pot( u, v ) - cost[v][u], par[v] = -u-1;
        
	// try edge u->v
	if( x[u][v] < cap[u][v] && d[v] > Pot(u,v) + cost[u][v] ) 
	  d[v] = Pot(u,v) + cost[u][v], par[v] = -u - 1;
      }
  }
  
  for (int i = 0; i < n; i++ ) if (pi[i] < INF) pi[i] += d[i];
  
  return par[t] >= 0;
}
#undef Pot

int mcmf(long long &fcost) {
  // build the adjacency list
  memset(nadj, 0, sizeof(nadj));
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++) 
      if(cap[i][j] || cap[j][i]) A[i][nadj[i]++] = j;
  
  memset(x, 0, sizeof(x));
  memset(pi, 0, sizeof(pi));
  int flow = fcost = 0;
    
  // repeatedly, find a cheapest path from s to t
  while(dijkstra(n, s, t)) {
    // get the bottleneck capacity
    int bot = INT_MAX;
    for(int v = t, u = par[v]; v != s; u = par[v = u])
      bot = min(bot, x[v][u] ? x[v][u] : (cap[u][v] - x[u][v]));

    // update the flow network
    for(int v = t, u = par[v]; v != s; u = par[v = u] )
      if(x[v][u]) { x[v][u] -= bot; fcost -= bot * cost[v][u]; }
      else { x[u][v] += bot; fcost += bot * cost[u][v]; }
    
    flow += bot;
  }
  
  return flow;
}

int main() {
  int i, j;
  int D, K;

  while (scanf("%d%d", &n, &m) == 2) {
    memset(cap, 0, sizeof(cap));
    memset(cost, 0, sizeof(cost));
    for (i = 0; i < m; i++) {
      int u, v;
      long long c;
      scanf("%d%d%lld", &u, &v, &c);
      cost[u][v] = cost[v][u] = c;
      cap[u][v] = cap[v][u] = 1;
    }
    scanf("%d%d", &D, &K);
    cost[0][1] = 0; cap[0][1] = D;
    for (i = 1; i <= n; i++)
      for (j = 1; j <= n; j++)
	cap[i][j] *= K;

    s = 0;
    t = n++;

    long long res;
    if (mcmf(res) != D)
      printf("Impossible.\n");
    else printf("%lld\n", res);

  }

  return 0;
}
