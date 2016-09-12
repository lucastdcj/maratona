/*%
Emparalhamento Bipartido de Custo Maximo
Autor: Chines/Davi Costa
Complexidade: O(n^3)
Tempo de implementacao: ?
Testes: nuevo-3987
Dependencias: Sem dependencias
Descricao: Encontra o emparelhamento maximo
  de custo maximo, para custo minimo insira as
  arestas com peso negativo. Se uma aresta nao
  existe o valor na matriz deve ser -1*INF.
  CUidado: NAO UTILIZAR MEMSET PARA O -1*INF
%*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

#define INF 0x3f3f3f3f
#define MAXN 351

int n, m; //# de vertices em cada lado
int adj[MAXN][MAXN]; /*Matriz de Adj*/
int labelx[MAXN], labely[MAXN], usedx[MAXN], usedy[MAXN], lnk[MAXN];
int mat; //Tamanho to match


//Auxiliar Caminho Aumentante
bool path(int i) {
  usedx[i] = 1;
  for (int j = 0; j < m; j++) {
    if (!usedy[j] && adj[i][j] != -INF && 
	!abs(adj[i][j] - labelx[i] - labely[j])) {
      usedy[j] = 1;
      if (lnk[j] == -1 || path(lnk[j])) {
	lnk[j] = i;
	return true;
      }
    }
  }
  return false;
}

//Apos preencher adj chamar match()
int match() {
  mat = 0;
  memset(lnk,-1,sizeof(lnk));
  memset(labely,0,sizeof(labely));
  for (int i = 0; i < n; i++) {
    labelx[i] = 0;
    for (int j = 0; j < m; j++)
      if (adj[i][j] > labelx[i]) labelx[i] = adj[i][j];
  }
  for (int k = 0; k < n; k++) {
    while (1) {
      memset(usedx,0,sizeof(usedx));
      memset(usedy,0,sizeof(usedy));
      if (path(k)) { mat++; break; }
      int delta = INF;
      for (int i = 0; i < n; i++)
	if (usedx[i])
	  for (int j = 0; j < m; j++)
	    if (!usedy[j] && adj[i][j] != -INF)
	      delta = min(delta,labelx[i] + labely[j] - adj[i][j]);
      if (delta == 0 || delta == INF) break;
      for (int i = 0; i < n; i++) 
	if (usedx[i]) labelx[i] -= delta;
      for (int j = 0; j < m; j++) 
	if (usedy[j]) labely[j] += delta;
    }
  }
  int sum = 0;
  for (int i = 0; i < n; i++) sum += labelx[i];
  for (int j = 0; j < m; j++) sum += labely[j];
  return sum;
}

/*Exemplo de uso com custo minimo*/
int main() {
  int k, e;
  int from, to, cost;
  scanf("%d",&k);
  for (int z = 0; z < k; z++) {
    if (z != 0) printf("\n");
    scanf("%d %d",&n,&m);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
	adj[i][j] = -INF;
    scanf("%d",&e);
    for (int i = 0; i < e; i++) {
      scanf("%d %d %d",&from,&to,&cost);
      adj[from][to] = -cost;
    }
    int r = -match();
    printf("%d\n",r);
  }
  return 0;
}
      
    

