/*%
Fluxo Máximo de Custo Mínimo
Autor: Frank Chu, Igor Naverniouk, Igor Assis
Complexidade: O(n^2*flow  <?  n^3*fcost)
Tempo de implementacao: ?
Testes: uva.10594 uva.10806
Descricao: Fluxo maximo de custo minimo entre dois vertices
           s e t usando algoritmo de caminhos aumentantes
           minimos.
%*/

#include <cstring>
#include <climits>
#include <algorithm> 

using namespace std;

// the maximum number of vertices + 1
#define MAXN 1024

/* FILL ME */
int cap[MAXN][MAXN];
int cost[MAXN][MAXN]; // cost per unit of flow matrix
int n, s, t;

// flow network and adjacency list
int x[MAXN][MAXN], adj[MAXN][MAXN], nadj[MAXN];

// Dijkstra's successor and depth
int par[MAXN], d[MAXN]; // par[source] = source;

// Labelling function
int pi[MAXN];

#define INF (0x3f3f3f3f)

// Dijkstra's using non-negative edge weights (cost+potential)
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
        if (x[u][v]<cap[u][v] && d[v]>Pot(u,v)+cost[u][v])
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
    int bot = INT_MAX;
    for(int v = t, u = par[v]; v != s; u = par[v = u])
      bot = min(bot, x[v][u] ? x[v][u] : (cap[u][v]-x[u][v]));

    // update the flow network
    for(int v = t, u = par[v]; v != s; u = par[v = u] )
      if(x[v][u]) { x[v][u] -= bot; fcost -= bot*cost[v][u]; }
      else { x[u][v] += bot; fcost += bot * cost[u][v]; }
    
    flow += bot;
  }
  
  return flow;
}

/**** Exemplo simples de uso ****/
#include <iostream>
#include <stdio.h>

using namespace std;

/*
 * PARAMETERS:
 *      - cap (global): adjacency matrix where
 *               cap[u][v] is the capacity of the edge u->v.
 *               cap[u][v] is 0 for non-existent edges.
 *      - cost (global): a matrix where cost[u][v] is the cost
 *               per unit of flow along the edge u->v.
 *               If cap[u][v] == 0, cost[u][v] is
 *               ignored. ALL COSTS MUST BE NON-NEGATIVE!
 *      - n: the number of vertices
 *      - s: source vertex.
 *      - t: sink.
 * RETURNS:
 *      - the flow
 *      - the total cost through 'fcost'
 *      - fnet contains the flow network. Careful:
 *           both fnet[u][v] and fnet[v][u] could be positive.
 *           Take the difference.
 */

int main() {
  cin >> n;
  memset( cap, 0, sizeof( cap ) );

  int m, a, b, c, cp;
  cin >> m;
  cin >> s >> t;
    
  // fill up cap with existing capacities.
  // if the edge u->v has capacity 6, set cap[u][v] = 6.
  // for each cap[u][v] > 0, set cost[u][v] to  the
  // cost per unit of flow along the edge u->v
  for (int i=0; i<m; i++) {
    cin >> a >> b >> cp >> c;
    cost[a][b] = c; // cost[b][a] = c;
    cap[a][b] = cp; // cap[b][a] = cp;
  }

  int fcost;
  int flow = mfmc(fcost);
  cout << "flow: " << flow << endl;
  cout << "cost: " << fcost << endl;
    
  return 0;
}
