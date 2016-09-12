/*%
  Log Discreto
  Autor: Marcelo Galvão Póvoa
  Complexidade: O(sqrt(m)*lg m)
  Testes: uva10225
  Descricao: Dados a, b e m (a e m devem ser coprimos),
             calcula o menor x tal que a^x = b (mod m)
  %*/
#include <cmath>
#include <map>
using namespace std;

int baby_giant(int a, int b, int m) {
  int n = ceil(sqrt(m));
  int an = 1;
  for (int i = 0; i < n; i++)
    an = (an * 1LL * a) % m;

  map<int, int> vals;
  for (int i = 0, cur = b; i <= n; i++) {
    vals[cur] = i;
    cur = (cur * 1LL * a) % m; // baby step
  }

  for (int i = 1, cur = an; i <= n; i++) {
    if (vals.count(cur)) {
      int ans = i*n - vals[cur];
      if (ans < m)
        return ans;
    }
    cur = (cur * 1LL * an) % m; // giant step
  }
  return -1;
} 

/**** Exemplo simples de uso ****/
int main() {
  int p, b, n;
  while (scanf("%d %d %d", &p, &b, &n) != EOF) {
    int x = baby_giant(b, n, p);
    
    if (x == -1) printf("no solution\n");
    else printf("%d\n", x);
  }   
  return 0;
} 
