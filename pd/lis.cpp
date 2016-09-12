/*%
  Longest Increasing Subsequence (LIS)
  Autor: Marcelo Galvão Póvoa
  Complexidade: O(n*lg k), sendo k o tamanho da LIS
  Testes: UVA.231 
  Descricao: Determina o tamanho da LIS do vetor v, 
  que pode ter numeros negativos, inclusive. Os trechos 
  de codigo comentados são  relativos apenas a parte 
  de reconstrucao de uma LIS. Esse algoritmo so funciona
  quando a relacao entre dois elementos eh transitiva 
  (a < b e b < c => a < c), como acontece com
  numeros, strings, etc.
  %*/

#include <stdio.h>
#include <string.h>
#define MAXN 1000
#define INF 0x3f3f3f3f

int v[MAXN+1] /*,ant[MAXN+1],li[MAXN+1]*/ ;
int pd[MAXN+1] /*,ipd[MAXN+1]*/ ; 
/*pd armazena o menor elemento que lide-
  ra uma IS de tamanho i ate o momento*/

int lis(int n) {
  int es,di,m,mx=0;
   
  memset(pd,0x3f,sizeof(pd));
  pd[0]=-INF;
   
  for (int i=0;i<n;i++) {
    es=0; di=i;
    while (es<di) {
      m=(es+di+1)/2;
      if (pd[m]<v[i]) es=m;
      else di=m-1;
    }
      
    if (pd[es]<v[i] && pd[es+1]>v[i]) {
      pd[es+1]=v[i];
      if (es+1>mx) mx=es+1;
      /* ipd[es+1]=i;
         ant[i]=ipd[es];*/
    }
  }
  return mx;
}

/*reconstroi uma IS de tamanho tam depois de chamar lis(n)*/
/*void build(int tam) { 
  int p=ipd[tam];
   
  if (pd[tam]==INF) printf("-1\n");
  else if (tam>0) {
    for (int i=0;i<tam;i++) {
      li[i]=v[p];
      p=ant[p];
    }
      
    for (int i=tam-1;i>0;i--) printf("%d ",li[i]);
    printf("%d\n",li[0]);
  }
  else printf("\n");
}*/

/**** Exemplo simples de uso ****/
int main() {
  int n,i,k;
   
  scanf(" %d",&n);
  for (i=0;i<n;i++) scanf(" %d",&v[i]);
   
  k=lis(n);
  printf("%d\n",k);
  /*build(k);*/
   
  return 0;
}
