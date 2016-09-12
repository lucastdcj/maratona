#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 40

char nome[MAXN][20];

/** ordenação topológica **/
int n;
int adj[MAXN][MAXN];
int nadj[MAXN];

int foi[MAXN], foi2[MAXN];
int tops[MAXN], ip;

int DFS(int k) {
  int i,j;

  foi[k] = foi2[k] = 1;
  for(j=0 ; j<nadj[k] ; j++) {
    i = adj[k][j];
    if(foi2[i]) return 0;
    if(!foi[i] && !DFS(i)) return 0;
  }

  tops[--ip] = k;
  foi2[k] = 0;

  return 1;
}

int ord_top() {
  int i;

  memset(foi, 0, n*sizeof(int));
  memset(foi2, 0, n*sizeof(int));
  ip = n;

  for(i=0 ; i<n ; i++)
    if(!foi[i] && !DFS(i)) return 0;

  return 1;
}
/** fim ordenação topológica **/

int busca(char *s) {
  int esq, dir, meio, cmp;

  esq = 0;
  dir = n-1;
  while(esq <= dir) {
    meio = (esq+dir)/2;

    cmp = strcmp(s, nome[meio]);
    if(cmp == 0) return meio;
    if(cmp < 0) dir = meio-1;
    else esq = meio+1;
  }

  return -1;
}

int main() {
  char nome_aux[20];
  int i,j, k,k2;
  int nt=0;

  while(scanf(" %d", &n)==1 && n) {
    for(i=0 ; i<n ; i++) {
      nadj[i] = 0;
      scanf(" %s", nome[i]);
    }

    qsort(nome, n, sizeof(nome[0]), strcmp);

    for(i=0 ; i<n ; i++) {
      scanf(" %s", nome_aux);
      k = busca(nome_aux);

      scanf(" %d", &j);
      while(j--) {
	scanf(" %s", nome_aux);
	k2 = busca(nome_aux);

	adj[k2][nadj[k2]++] = k;
      }
    }

    printf("Teste %d\n", ++nt);

    if(!ord_top()) printf("impossivel");
    else {
      for(i=0 ; i<n ; i++)
	printf("%s ", nome[tops[i]]);
    }

    printf("\n\n");
  }

  return 0;
}
