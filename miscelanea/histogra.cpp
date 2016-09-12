/*%
  Maior Retângulo em um Histograma
  Autor: Marcelo Galvão Póvoa
  Complexidade: O(n)
  Testes: SPOJ.HISTOGRA
    Descricao: Dado um vetor que contem alturas (>=0) das
  barras de um histograma de largura fixa = 1, calcula
  a área do maior retangulo contido no histograma
  %*/
  
#include <algorithm>
#define MAX 100100
using namespace std;

int sh[MAX], sp[MAX];

long long histogram(int *v, int n) {
  int qs=1, curh=0;
  long long res=0;

  sh[0]=-1; sp[0]=0;
  v[n]=-1;
  
  for (int i=0; i<n+1; i++) {
    if (i<n && v[i]>=curh) {
      sh[qs]=v[i];
      sp[qs++]=i;
    }
    else {
      while (sh[qs-1]>v[i]) {
        qs--;
        res=max(res, (long long) sh[qs]*(i-sp[qs]));
      }
      sh[qs++]=v[i];
    }
    curh=v[i];
  }

  return res;
}

/**** Exemplo simples de uso ****/
#include <cstdio>

int main() {
  int n;
  int v[MAX];

  while (scanf("%d",&n)==1 && n) {
    for (int i=0; i<n; i++)
      scanf(" %d", &v[i]);

    printf("%lld\n",histogram(v,n));
  }
  return 0;
}
