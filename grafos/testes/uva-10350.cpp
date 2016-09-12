#include <string.h>
#include <iostream>
#include <string>
#include <limits.h>

using namespace std;

#define MAXN 3000
#define INF 0x3f3f3f

int pai[MAXN]; //pai de cada vertice
int graph[MAXN][MAXN]; //lista de adj.
int custo[MAXN][MAXN]; //refere-se a aresta de graph
int nadj[MAXN]; //grau de cada vertice
int d[MAXN]; //distancia de s ateh cada vertice

/** ordenação topológica **/
int foi[MAXN], foi2[MAXN];
int tops[MAXN], ip;

int DFS(int k) {
  int i,j;

  foi[k] = foi2[k] = 1;
  for(j=0 ; j<nadj[k] ; j++) {
    i = graph[k][j];
    if(foi2[i]) return 0;
    if(!foi[i] && !DFS(i)) return 0;
  }

  tops[--ip] = k;
  foi2[k] = 0;

  return 1;
}

int ord_top(int n) {
  int i;

  memset(foi, 0, n*sizeof(int));
  memset(foi2, 0, n*sizeof(int));
  ip = n;

  for(i=0 ; i<n ; i++)
    if(!foi[i] && !DFS(i)) return 0;

  return 1;
}
/** fim ordenação topológica **/


void calc_path(int s, int n) {
  ord_top(n);
  memset(pai,-1,sizeof(pai));
  for (int i = 0; i < n; i++) d[i] = INF;
  d[s] = 0;
  pai[s] = 0;
  for (int i = 0; i < n; i++) {
    int x = tops[i];
    if (pai[x] == -1) continue;
    for (int j = 0; j < nadj[x]; j++) {
      int v = graph[x][j];
      int cost = custo[x][j];
      if (d[v] > d[x] + cost) {
	d[v] = d[x] + cost;
	pai[v] = x;
      }
    }
  }
}

int main() {
  string s;
  int n, m, cost;
  while (cin >> s) {
    cost=0;
    memset(nadj,0,sizeof(nadj));
    scanf("%d %d",&n,&m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
	int v = i*m + j;
	for (int k = 0; k < m; k++) {
	  int u = (i+1)*m + k;
	  if (i != 0) scanf("%d",&cost);
	  graph[v][nadj[v]] = u;
	  custo[v][nadj[v]++] = cost;
	}
      }
    }
    calc_path(0,m*(n+1));
    int mini = INT_MAX;
    for (int i = m*n; i <= m*n + m -1; i++) {
      mini = min(mini,d[i]);
    }
    mini += 2*(n-1);
    cout << s << endl << mini << endl;
  }
  return 0;
}
