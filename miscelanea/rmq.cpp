/*%
Range Minimum Query (RMQ)
Autor: NU 2/Marcelo Galvão Póvoa
Complexidade: O(n lg n)-preprocessamento e O(1)-consulta
Tempo de implementacao: 7 min
Testes: Testes proprios aleatorios
Descricao: Apos o preprocessamento de um vetor v, o algoritmo
responde de forma eficiente o indice do elemento minimo em
v[a..b]. Em caso de empate, é devolvido o maior índice.
Caso queira o menor, descomente o = em pairmin()
%*/
using namespace std;
#define N 100100
#define LOG 16     // piso de log2(N)

int *va, Log2[N], p[LOG+1][N];

int pairmin(int i1, int i2) {
   return va[i1]</*=*/va[i2] ? i1:i2;
}

void init(int *a, int n) {
  va = a;
  for (int i=1,k=0; i<=n; i++) {
    Log2[i] = k;
    if (1 << (k+1) == i) k++;
  }

  int ln = Log2[n];
  for (int i=0; i<n; i++) p[0][i]=i;
  for (int i=1; i<=ln; i++) 
    for (int j=0; j + (1 << i) - 1 < n; j++) {
      int i1 = p[i-1][j];
      int i2 = p[i-1][j+ (1 << i-1)];
      p[i][j] = pairmin(i1, i2);
    }
}
   
int query(int b, int e) {
  int ln = Log2[e - b + 1];
  int i1 = p[ln][b];
  int i2 = p[ln][e - (1 << ln) + 1];
    
  return pairmin(i1,i2);
}

/**** Exemplo simples de uso ****/
#include <cstdio>
int main(){
   int i,n,x;
   int vet[1000];
   
   scanf(" %d",&n);
   for (i=0;i<n;i++) {
      scanf(" %d",&x);
      vet[i]=x;
   }
   
   init(vet, n);
   printf("%d\n",query(0,n-1)); 
   /*imprime o maior indice de um menor elemento*/
   
   return 0;
}
