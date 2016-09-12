/*%
Array de Sufixos
Autor: Marcelo Galvão Póvoa
Complexidade: O(n*lg^2(n))
Descricao: Gera o indice de cada sufixo quando ordenados
lexicograficamente. A matriz p[i][j] contem os indices para 
prefixos de sufixos em j de tamanho (1<<i)
A funcao lcp(i,j) calcula o maior prefixo comum dos suf i e j
%*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define MAX 201000
#define LOGM 19

int p[LOGM][MAX],n,ps;
pair< pair<int,int> , int> vp[MAX];
char s[MAX];

//requer precalculo de p[][]
int lcp(int x, int y) {
  int res=0;

  if (x==y) return n-x;
  
  for (int k=ps-1; k>=0; k--)
    if (p[k][x+res]==p[k][y+res]) {
      res+=(1<<k);
      if (x+res>=n || y+res>=n) break;
    }
  return res;
}

void suffarr() {
  for (int i=0; i<n; i++) p[0][i]=s[i];
  ps=1;
  
  for (int pow=1, k=0; pow<n; pow*=2, k++) {
    for (int i=0; i<n; i++) {
      int x;
      if (i+pow>=n) x=-1;
      else x=p[k][i+pow];
      
      vp[i]=make_pair(make_pair(p[k][i],x), i);
    }
    
    sort(vp,vp+n);
    int id=0;
    p[k+1][vp[0].second]=0;
    for (int i=1; i<n; i++) {
      if (vp[i].first!=vp[i-1].first) id++;
      p[k+1][vp[i].second]=id;
    }
    ps=k+2; //qtde de linhas da tabela
  }
}

int main() {
  scanf(" %d",&n);
  scanf(" %s",s);
  suffarr();
  
  int res=0;
  vector<pair<int, int> > vp;
  for (int i=0; i<n; i++)
    vp.push_back(make_pair(p[ps-1][i], i));
  sort(vp.begin(), vp.end()); //guarda o suffarr ordenado
  
  for (int i=0; i<n-1; i++) 
    res=max(res,lcp(vp[i].second, vp[i+1].second));
  printf("%d\n",res);
}
