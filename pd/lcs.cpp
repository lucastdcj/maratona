/*%
  Longest Common Subsequence (LCS)
  Autor: Davi Costa/Marcelo Galvão Póvoa
  Complexidade: O(n*m)-calculo e O(n+m)-reconstrucao
  Tempo de implementacao: 5 min
  Testes: UVA.10066, UVA.10405
    Descricao: Calcula o tamanho de uma LCS entre duas strings e
  reconstroi uma de tamanho qualquer (nao maior que
  o maximo).
  %*/
#include <stdio.h>
#include <string.h>
#define MAX 1234

/*Primeira e segunda strings (tamanhos m e n)*/
char seq[2][MAX+1]; 
int pd[MAX+1][MAX+1];

/*guarda o caminho*/
enum { cima, lado, diag } way[MAX+1][MAX+1]; 

int lcs(int m, int n) {
  int i,j;
  for (i = 0; i <= m; i++) pd[i][0] = 0;
  for (i = 0; i <= n; i++) pd[0][i] = 0;   

  for (i = 1; i <= m; i++)
    for (j = 1; j <= n; j++) {
      if (seq[0][i-1] == seq[1][j-1]) {
        pd[i][j] = pd[i-1][j-1] + 1;
        way[i][j] = diag;
      }
      else if (pd[i-1][j] > pd[i][j-1]) {
        pd[i][j] = pd[i-1][j];
        way[i][j] = cima;
      }
      else {
        pd[i][j] = pd[i][j-1];
        way[i][j] = lado;
      }
    }
  return pd[m][n];
}

/*reconstroi uma CS, deve ser chamada com (m-1,n-1,tam CS)*/
void printway(int i, int j, int k) { 
  if (i==0 || j==0 || k==0) printf("\n");
  else if (way[i][j] == diag) {
    printway(i-1, j-1, k-1);
    printf("%c",seq[0][i]);
  }
  else if (way[i][j]==cima) printway(i-1, j, k-1);
  else printway(i, j-1, k-1);
}

/**** Exemplo simples de uso ****/
int main(){
  int n,m;
  while (1) {
    scanf(" %s",seq[0]);
    scanf(" %s",seq[1]);
    m=strlen(seq[0]);
    n=strlen(seq[1]);
      
    printf("%d\n",lcs(m,n));
  }
  return 0;
}
