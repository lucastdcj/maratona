#include <iostream>
#include <queue>
#include <limits.h>
#include <map>
#include <string>
#include <vector>

#define pb push_back

using namespace std;

#define NN 10123

int deg[NN];
vector<int> adj[NN], graph[NN];
int d[NN], q[NN], inq[NN], prev[NN], qs;

#define CLR( x, v ) memset( x, v, sizeof( x ) )
#define BUBL { \
    t = q[i]; q[i] = q[j]; q[j] = t; \
    t = inq[q[i]]; inq[q[i]] = inq[q[j]]; inq[q[j]] = t; }

int dijkstra( int n, int s, int t )
{
    CLR( d, 9 ); CLR( inq, -1 ); CLR( prev, -1 );
    d[s] = qs = 0;
    inq[q[qs++] = s] = 0;
    prev[s] = -2;
    
    while( qs )
    {
        // get the minimum from the q
        int u = q[0]; inq[u] = -1;
        
        // bubble down
        q[0] = q[--qs];
        if( qs ) inq[q[0]] = 0;
        for( int i = 0, j = 2*i + 1, t; j < qs; i = j, j = 2*i + 1 )
        {
            if( j + 1 < qs && d[q[j + 1]] < d[q[j]] ) j++;
            if( d[q[j]] >= d[q[i]] ) break;
            BUBL;
        }
        
        // relax neighbours
        for( int k = 0, v = adj[u][k]; k < deg[u]; v = adj[u][++k] )
        {
            int newd = d[u] + graph[u][k];
            if( newd < d[v] )
            {
                d[v] = newd;
                prev[v] = u;
                if( inq[v] < 0 ) { inq[q[qs] = v] = qs; qs++; }
                
                // bubble up
                for( int i = inq[v], j = ( i - 1 )/2, t; 
                     d[q[i]] < d[q[j]]; i = j, j = ( i - 1 )/2 )
                     BUBL;
            }
        }
    }
    
    return d[t];
}


/**** Exemplo simples de uso ****/
int main() {
  int k;
  int n, l, t;
  int to, cost;
  map<string,int> m;
  string s1, s2;
  scanf("%d",&k);
  while (k) {
    k--;
    m.clear();
    memset(deg,0,sizeof(deg));
    scanf("%d",&n);
    for (int i = 0; i <= n; i++) {
      adj[i].clear();
      graph[i].clear();
    }
    for (int i = 1; i <= n; i++) {
      cin >> s1;
      m[s1] = i;
      scanf("%d",&l);
      for (int j = 0; j < l; j++) {
	scanf("%d %d",&to,&cost);
	adj[i].pb(to);
	graph[i].pb(cost);
	deg[i]++;
      }
    }
    scanf("%d",&t);
    for (int i = 0; i < t; i++) {
      cin >> s1 >> s2;
      printf("%d\n",dijkstra(n+1,m[s1],m[s2]));
    }
  }
  return 0;
}
