/*%
Caminho Mínimo em um DAG
Autor: NBMundial / Davi Costa
Complexidade: O(E + V)
Tempo de implementacao: ?
Testes: uva-10350
Dependencias: Topological Sort
Descricao: Caminho minimo em DAG
%*/

#define MAXN 100
#define INF 0x3f3f3f

/* FILL ME */
int nadj[MAXN]; //grau de cada vertice
int adj[MAXN][MAXN]; //lista de adj.
int custo[MAXN][MAXN]; //refere-se a aresta de adj

int pai[MAXN]; //se precisar reconstruir o caminho
int d[MAXN]; //distancia de s ateh cada vertice
int tops[MAXN]; //topological sort
int path[MAXN]; //caminho ate t
bool used[MAXN];
int ip;

/*
n: numero de vertices, s: origem
*/
int calc_path(int n, int s) {
  topsort(n);
  memset(pai,-1,sizeof(pai));
  for (int i = 0; i < n; i++) d[i] = INF;
  d[s] = 0;
  pai[s] = 0;
  for (int i = 0; i < n; i++) {
    int x = tops[i];
    if (pai[x] == -1) continue;
    for (int j = 0; j < nadj[x]; j++) {
      int v = adj[x][j];
      int cost = custo[x][j];
      if (d[v] > d[x] + cost) {
        d[v] = d[x] + cost;
        pai[v] = x;
      }
    }
  }
}

/*Exemplo de uso*/

int main() {
  int n, m;
  int origem,destino;
  int from, to, cost;
  while (scanf("%d %d",&n,&m) == 2 && n != 0) {
    scanf("%d %d",&origem,&destino);
    memset(nadj,0,sizeof(nadj));
    for (int i = 0; i < m; i++) {
      scanf("%d %d %d",&from,&to,&cost);
      custo[from][nadj[from]] = custo[to][nadj[to]] = cost;
      adj[from][nadj[from]++] = to;
      adj[to][nadj[to]++] = from;
    }
    shortdag(n,origem);
    printf("%d\n",d[destino]);
  }
  return 0;
}
