//0.020

#include <iostream>

using namespace std;

#define NN 110

int graph[NN][NN], adj[NN][NN], deg[NN];
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
            int newd = d[u] + graph[u][v];
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


int main() {
  int n;
  int cost;
  int far;
  char c;
  scanf("%d",&n);
  CLR(deg,0);
  for (int i = 0; i < n; i++) graph[i][i] = 0;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (scanf("%d",&cost) != 1) {
	scanf("%c",&c);
	continue;
      }
      graph[i][j] = graph[j][i] = cost;
      adj[i][deg[i]++] = j;
      adj[j][deg[j]++] = i;
    }
  }
  dijkstra(n,0,0);
  far = 0;
  for (int i = 0; i < n; i++) {
    if (d[i] > far) far = d[i];
  }
  printf("%d\n",far);
  return 0;
}


