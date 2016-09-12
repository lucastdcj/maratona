/*%
Teorema Chinês do Resto
Autor: NU 2/Marcelo Galvão Póvoa
Complexidade: O(n * lg X)
Tempo de implementacao: 4 min
Testes: Testes proprios
Dependencias: Algoritmo de Euclides Extendido
Descricao: Resolve o conj de eqs: a[i]*x === b[i] (mod m[i])
           para 0<=i<n com a restricao m[i]>1
           Se a[i] == 1 para todo i, existe solucao sse
           b[i]===b[j] (mod gcd(m[i],m[j])) para todo i e j 
%*/

#include <algorithm>
#include <vector>
#define MAXN 1000
using namespace std;

int n,a[MAXN],b[MAXN],m[MAXN];
typedef pair<int,int> pii;




int chines() {
   int x = 0, M = 1;
   for (int i=0; i<n; i++) {
     int b2 = b[i] - a[i]*x;
     pii bizu = mdc(a[i]*M, m[i]);
     int g = a[i]*M * bizu.first + m[i] * bizu.second;
     
     if (b2 % g) return -1;
     x += M *(bizu.first * (b2/g) % (m[i]/g));
     M *= (m[i]/g);
   }
   return (x%M+M)%M;
}

/**** Exemplo simples de uso ****/
int main(){
   int i;
   
   scanf(" %d",&n);
   for (i=0;i<n;i++) scanf(" %d %d %d",&a[i],&b[i],&m[i]);
   
   printf("%d\n",chines());
   return 0;
}
