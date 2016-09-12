/*%
  Árvore de Intervalos
  Autor: Marcelo Galvão Póvoa
  Complexidade: O(lg n) por update/query
  Testes: SPOJ.QTREE
    Descricao: Modelo de segtree que deve ser adaptado ao problema
  desejado. Suporta query em intervalo e update em ponto. O código
  abaixo é de RMQ, ou seja, dá o máximo elemento em um intervalo
  %*/

#include <cstring>
#include <algorithm>
#define MAXN 100100
using namespace std;

int t[4*MAXN];

/* Obtém o RMQ em [a,b]; chamar com root=0, rl=0, rr=n-1 */
int query(int root, int rl, int rr, int a, int b) {
  if (a > b) return 0;
  if (rl==a && rr==b) return t[root];
  
  int rm = (rl+rr)/2;
  return max(query(2*root+1, rl, rm, a, min(b, rm)), 
             query(2*root+2, rm+1, rr, max(a, rm+1), b));
}

/* Muda posição x para vx; chamar com root=0, rl=0, rr=n-1 */
void update(int root, int rl, int rr, int x, int vx) {
  if (rl==rr) t[root] = vx;
  else {
    int rm = (rl+rr)/2;
    if (x <= rm) update(2*root+1, rl, rm, x, vx);
    else update(2*root+2, rm+1, rr, x, vx);
    
    t[root] = max(t[2*root+1], t[2*root+2]);
  }
}

/**** Exemplo simples de uso ****/
int main() {
    int n,c,op,x,y;

    while (scanf("%d%d",&n,&c)==2) {
        memset(t, 0, sizeof(t));
        
        while (c--) {
          scanf("%d %d %d",&op,&x,&y);
          if (op==0) update(0, 0, n-1, x, y);
          else printf("%d\n", query(0, 0, n-1, x, y));
        }
    }
    return 0;
}
