#include <iostream>
#include <string>
#include <limits.h>
#include <string.h>

using namespace std;

#define MAXN 3000
#define INF 0x3f3f3f

int pai[MAXN]; /* se precisar reconstruir o caminho */
int graph[MAXN][MAXN]; /* lista de adj */
int custo[MAXN][MAXN]; /* refere-se a aresta de adj */
int nadj[MAXN]; /* grau de cada vertice */

int D[MAXN]; /* distancia de cada vertice até b */
int foi[MAXN];

void minDFS(int k) {
  int i,j,c;
  foi[k]=1;
  for(j=0 ; j<nadj[k] ; j++) {
    i = graph[k][j];
    c = custo[k][j];

    if(!foi[i]) minDFS(i);
    if(D[k] > D[i]+c) {
      D[k] = D[i]+c;
      pai[k] = i;
    }
  }
}

void minDAG(int a, int n) {
  int i;
  memset(D, 0x3f, n*sizeof(int));
  memset(foi, 0, n*sizeof(int));
  D[a] = 0;
  for(i=0 ; i<n ; i++)
    if(!foi[i]) minDFS(i);
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
//	  graph[v][nadj[v]] = u;
//	  custo[v][nadj[v]++] = cost;
	  graph[u][nadj[u]] = v; // inserir arestas invertidas!
	  custo[u][nadj[u]++] = cost;
	}
      }
    }
    minDAG(0,m*(n+1));
    int mini = INT_MAX;
    for (int i = m*n; i <= m*n + m -1; i++) {
      mini = min(mini,D[i]);
    }
    mini += 2*(n-1);
    cout << s << endl << mini << endl;
  }
  return 0;
}
