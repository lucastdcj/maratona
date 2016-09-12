/*%
Operações com Matriz de Bits
Autor: Davi Costa
Complexidade:
Tempo de implementacao: 5~7 min
Testes: uva-11862
Descricao: Suporta todas as operacoes comuns de 
  matrizes utilizando um vetor de inteiros.
  OBS: A coluna 0 é representada na direita
  (bit menos significativo) e nao na esquerda
  como estamos acostumados.
%*/

#include <cstdio>
#include <cstring>
using namespace std;

#define MAX 32

typedef unsigned int ui;

class bm {
public:
  ui n, m;
  ui t[MAX];
  bm(ui nn, ui mm) {
    n = nn;
    m = mm;
    for (ui i = 0; i < nn;i++) t[i] = 0;
  }
  bm & operator=(const bm &b) { //copia
    n = b.n;
    m = b.m;
    for (ui i = 0; i < n;i++) t[i] = b.t[i];
    return *this;
  }
  ui& operator [] (ui r) { return t[r]; } //pega toda linha r
  //pega o bit r,c
  bool operator () (ui r, ui c) {return (t[r] & (1<<c)) != 0;}
  void set(ui r, ui c) { t[r] |= 1<<c; } //seta bit r,c
  void clear(ui r, ui c) { t[r] &= ~(1<<c); } //limpa bit r,c
  bm transp() { //transpoe uma matriz
    bm res(m,n);
    for (ui i = 0; i < n; i++) {
      ui a = t[i];
      for (int j = m-1; j >= 0; j--, a>>=1)
        if (a&1)  res.set(j,n-i-1);
    }
    return res;
  }      
  bm operator * (bm &m2) { //multiplica 2 matrizes
    bm trans = m2.transp();
    ui m = m2.m; bm res(n,m);
    for (ui i = 0; i < n; i++)
      for (ui j = 0; j < m; j++) {
        ui r = __builtin_popcount(t[i]&trans[j])%2;
        if (r) res.set(i,m-j-1);
      }
    return res;
  }
  ui mul2(ui a) { //multiplica matriz por um vetor Mx1
    ui res = 0;
    for (ui i = 0; i < n; i++) {
      ui r = __builtin_popcount(t[i]&a)%2;
      res |= r<<(n-i-1);
    }
    return res;
  }
  bm pot(ui k) { //exponenciacao em logn
    bm res(n,n);
    if (k == 0) {
      for (ui i = 0; i < n; i++) res.set(n-i-1,i);
      return res;
    }
    if (k == 1) return *this;
    ui l = k/2;
    res = pot(l);
    if (k%2) return res*res*(*this);
    return res*res;
  }
  void print() { //imprime
    for (ui i = 0; i < n; i++) {
      for (ui j = m; j > 0; j--) {
        printf("%d",(*this)(i,j-1));
      }
      printf("\n");
    }
    printf("\n");
  }
};

/**** Exemplo simples de uso ****/
int main() {
  int n = 5, m = 5;
  bm mat(n,m);
  for (int i = 0; i < n; i++) mat[i] = 1<<i;
  bm mattransp = mat.transp();
  bm mat2 = mat*mat;
  mat.print();
  mattransp.print();
  mat2.print();
  return 0;
}

