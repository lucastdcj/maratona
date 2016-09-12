/*%
  Gray Code
  Autor: Douglas Santos
  Complexidade: O(1)
  Testes: uva-12447.cpp
    Descricao: Calcula o código de gray, o inverso
  do código de gray e o código de gray invertido.
  %*/

/* Retorna o i-ésimo elemento do código de gray */
int gray(int i) {
  return i ^ ( i >> 1 ) ;
}

/* Retorna a posição de um elemento no código de gray */ 
int inverso_gray(int g) {
  int n = 0;
  for (; g; g >>= 1)
    n ^= g;
  return n;
}

/* Retorna o i-ésimo elemento do código de gray invertido
   de n bits. No código de gray invertido, o sucessor de
   um elemento tem apenas 1 bit igual a ele */
int gray_invertido(int i, int n) {
  int y = i;
  if (i % 2) y = i ^ ((1 << n) - 1);
  int x = ((i/2) | (i & ((n % 2) * (1 << (n-1))))) ^ y;
  return x;
}
