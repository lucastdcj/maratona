/*%
Hash de Strings
Autor: Douglas Santos / Marcelo Póvoa
Complexidade: O(n)
Testes: Codeforces.7D, uva 12494, sgu 439
Descricao: Após preprocessar uma string, calcula o hash
de qualquer substring sua em tempo constante.
%*/

#include <algorithm>
#define MAXN 100100
#define B 33
using namespace std;
typedef unsigned long long hash;

hash h[MAXN], pwr[MAXN];
char s[MAXN];

void gen(char *s) {
  h[0] = 0;
  pwr[0] = 1;
  for (int i = 0; s[i]; i++) {
    h[i+1] = h[i] * B + s[i];
    pwr[i+1] = pwr[i] * B;
  }
}

// Calcula o hash da substring s[a..b]
hash sect(int a, int b) {
  if (a > b) return 0;
  return h[b+1] - h[a] * pwr[b - a + 1];
}

// Maior prefixo comum das substrings s[a..n-1], s[b..n-1]
int lcp(int a, int b, int n) {
  int es = 0, di = min(n-b, n-a);

  while (es < di) {
    int me = (es+di+1)/2;
    if (sect(a, a+me-1) == sect(b, b+me-1)) es = me;
    else di = me-1;
  }
  return es;
}

/**** Exemplo simples de uso ****/
int main() {
  while (scanf(" %s",s)==1) {
    gen(s);
    printf("%llu\n", sect(0, strlen(s) - 1));
  }
  return 0;
}
