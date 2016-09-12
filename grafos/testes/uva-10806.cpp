#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

// the maximum number of vertices + 1
#define MAXN 112

// adjacency matrix (fill this up)
int cap[MAXN][MAXN];

// cost per unit of flow matrix (fill this up)
int cost[MAXN][MAXN];

// flow network and adjacency list
int n, m, s, t;
int x[MAXN][MAXN], adj[MAXN][MAXN], nadj[MAXN];

// Dijkstra's successor and depth
int par[MAXN], d[MAXN]; // par[source] = source;

// Labelling function
int pi[MAXN];

#define INF (0x3f3f3f3f)

// Dijkstra's using non-negative edge weights (cost + potential)
#define Pot(u,v) (d[u] + pi[u] - pi[v])
bool dijkstra( int n, int s, int t ) {
  for( int i = 0; i < n; i++ ) d[i] = INF, par[i] = -1;
  d[s] = 0;
  par[s] = -n - 1;

  for (;;) {
    // find u with smallest d[u]
    int u = -1, bestD = INF;
    for(int i = 0; i < n; i++) if (par[i] < 0 && d[i] < bestD)
				 bestD = d[u = i];
    if(bestD == INF) break;

    // relax edge (u,i) or (i,u) for all i;
    par[u] = -par[u] - 1;
    for (int i = 0; i < nadj[u]; i++)
      {
	// try undoing edge v->u      
	int v = adj[u][i];
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

int mfmc(int &fcost) {
  // build the adjacency list
  memset(nadj, 0, sizeof(nadj));
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++) 
      if(cap[i][j] || cap[j][i]) adj[i][nadj[i]++] = j;
  
  memset(x, 0, sizeof(x));
  memset(pi, 0, sizeof(pi));
  int flow = fcost = 0;
    
  // repeatedly, find a cheapest path from s to t
  while(dijkstra(n, s, t)) {
    // get the bottleneck capacity
    int bot = INF;
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
  int i, fcost;  
  int u, v, c;

  for (;;) {
    scanf("%d%d", &n, &m);
    if (!n) break;
    memset(cap, 0, sizeof(cap));
    for (i = 0; i < m; i++) {
      scanf("%d%d%d", &u, &v, &c); u--; v--;
      cap[u][v] = cap[v][u] = 1;
      cost[u][v] = cost[v][u] = c;
    }
    
    s = n;
    t = n-1;
    n++;
    cap[s][0] = 2; cost[s][0] = 0;
    
    if (mfmc(fcost) < 2)
      printf("Back to jail\n");
    else printf("%d\n", fcost);

  }

  return 0;
}

