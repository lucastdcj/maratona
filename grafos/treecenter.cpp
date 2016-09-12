/*%
Centro de uma Árvore
Autor: Douglas Santos
Complexidade: O(n)
Testes: uva.12489
Descricao: Encontra o centro de uma árvore.
O centro de uma árvore é formado por um ou dois
vértices tal que esses vértices são os mais distantes
de um folha.
%*/

#include <cstdio>
#include <vector>
using namespace std;

#define MAXN 100010

/* FILL ME */
int n;
vector<int> adj[MAXN]; 

int de[MAXN];
int x[2][MAXN];

/* Retorna o par de vértice que forma o centro da árvore.
Se o centro tiver apenas um vértice, retorna -1 pro
segundo vértice do par */
pair<int, int> cTree(int n, vector<int> adj[]) {
  int c[2] = {0, 0};
  int ind = 0;
  int r = n;
  for (int i = 0; i < n; i++) {
    de[i] = adj[i].size();
    if (de[i] <= 1) {
      x[ind][c[ind]++] = i;
      r = r - 1;      
    }
  }
  while (r > 0) {
    int ot = (ind + 1) % 2;
    c[ot] = 0;
    for (int i = 0; i < c[ind]; i++) {
      int u = x[ind][i];
      for (int j = 0; j < adj[u].size(); j++) {
        int v = adj[u][j];
        de[v] = de[v] - 1;
        if (de[v] == 1) {
          x[ot][c[ot]++] = v;
          r = r - 1;      
        }       
      }
    }
    ind = ot;       
  }
  if (c[ind] == 1) return make_pair(x[ind][0], -1);
  return make_pair(x[ind][0], x[ind][1]);
}

/**** Exemplo simples de uso ****/
int main() {

  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    adj[i].clear();
  }
  int u, v;
  for (int i = 0; i < n-1; i++) {
    scanf("%d %d", &u, &v); 
    u--;
    v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  pair<int, int> p;
  p = cTree(n, adj);
  printf("Centro(s) da arvore: %d ", p.first + 1);
  if (p.second != -1) printf("%d", p.second + 1);
  printf("\n");
  return 0;
}
