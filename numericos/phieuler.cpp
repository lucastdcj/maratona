/*%
  Phi de Euler
  Autor: Douglas Santos
  Complexidade: O(sqrt(n))
  Testes: uva-12493, uva-12425
    Descricao: Calcula o número de elementos 
  coprimos a n, no intervalo [1, n].
  %*/

typedef long long int int64;

int64 phi(int64 n) {
  int64 res = n ;
  for (int64 i = 2; i * i <= n; ++i)
    if (n % i == 0) {
      while (n % i == 0)
        n /= i;
      res -= res / i;
    }
  if (n > 1)
    res -= res / n;
  return res;
} 

