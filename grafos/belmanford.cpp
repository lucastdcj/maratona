/*%
Bellman Ford
Autor: Igor Assis/Davi Costa
Complexidade: O(n*m)
Tempo de implementacao: ?
Testes: uva.10806, uva.423
Dependencias: Sem dependencias
Descricao: Caminho minimo com pesos negativos
%*/

#define MAXN 100 //Numero maximo de vertices
#define MAXM 10000 //Numero maximo de arestas
#define INF 0x3f3f3f3f

/* aresta (u,v) com peso w:
   orig[i] = u, dest[i] = v, peso[i] = w
   d[u], distancia da origem s ao vertice u
*/

/* FILL ME */
int orig[MAXM], dest[MAXM], peso[MAXM];

int d[MAXN], pai[MAXN];
/* 
s: origem, n: numero de vertices, m: numero de arestas
retorna 1 se o grafo nao tem ciclo negativo alcancavel
a partir de s, 0 c.c 
*/

int bellman_ford(int s, int n, int m) {
  int i, j;
  memset(pai,-1,sizeof(pai));
  pai[s] = s;
  for (i = 0; i < n; i++)
    d[i] = INF;
  d[s] = 0;
  for (i = 0; i < n-1; i++)
    for (j = 0; j < m; j++) {
      int u = orig[j], v = dest[j], w = peso[j];
      if (d[u] != INF && d[v] > d[u]+w) {
        d[v] = d[u]+w;
        pai[v] = u;
      }
    }
  for (j = 0; j < m; j++) {
    int u = orig[j], v = dest[j], w = peso[j];
    if (d[u] != INF && d[v] > d[u]+w) return 0;
  }
  return 1;
}

/**** Exemplo simples de uso ****/
int main() {
  int n, m;
  int from, to, cost;
  int origem, destino;
  while (scanf("%d %d",&n,&m) == 2 && n != 0) {
    int k = 0;
    for (int i = 0; i < m; i++) {
      scanf("%d %d %d",&from,&to,&cost);
      orig[k] = from;
      dest[k] = to;
      peso[k] = cost;
      k++;
      orig[k] = to;
      dest[k] = from;
      peso[k] = cost;
      k++;
    }
    scanf("%d %d",&origem,&destino);
    bellman_ford(origem,n,m);
    printf("%d\n",d[destino]);
  }
  return 0;
}
