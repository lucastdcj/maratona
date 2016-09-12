/*%
Topological Sort
Autor: Alexandre Kunieda
Complexidade: O(E + V)
Tempo de implementacao: ?
Testes: uva-10350 auxiliar para shortdag, spojbr-ORKUT
Dependencias: Nenhuma
Descricao: Ordena Topologicamente, ou verifica que não há
ordenação topológica. Para verificação de existência da
ordenação, implemente os trechos comentados do código;
além disso, as duas funções podem ser declaradas como void.
%*/

int n;
int adj[MAXN][MAXN]; /* lista de adj */
int nadj[MAXN]; /* grau de cada vertice */

int foi[MAXN], ip; /* auxiliar */
/* int foi2[MAXN]; */
int tops[MAXN]; /* resposta */

int DFS(int k) {
  int i,j;

  foi[k] = /* foi2[k] = */ 1;
  for(j=0 ; j<nadj[k] ; j++) {
    i = adj[k][j];
    /* if(foi2[i]) return 0; */
    if(!foi[i] && !DFS(i)) return 0;
  }

  tops[--ip] = k;
  /* foi2[k] = 0; */

  return 1;
}

/*
popular n: numero de vertices
apos chamar ord_top() "tops" tera a solucao
*/
int ord_top() {
  memset(foi, 0, n*sizeof(int));
  /* memset(foi2, 0, n*sizeof(int)); */
  ip = n;

  for(int i=0 ; i<n ; i++)
    if(!foi[i] && !DFS(i)) return 0;

  return 1;
}

/**** Exemplo simples de uso ****/
int main() {
  int m,i, from,to;
  while (scanf("%d %d",&n,&m) == 2 && n != 0) {
    memset(nadj,0,sizeof(nadj));
    for (i = 0; i < m; i++) {
      scanf("%d %d",&from,&to);
      adj[from][nadj[from]++] = to;
    }
    if(!ord_top()) puts("não há ordenação topológica");
    else for (i = 0; i < n; i++) printf("%d ",tops[i]);
  }
  return 0;
}
