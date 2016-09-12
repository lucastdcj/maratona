/*%
Cobertura Mínima por Caminhos em DAG
Autor: Douglas Santos
Complexidade: O(n*m)
Dependências: Emparelhamento Máximo Bipartido
Testes: SRM557-div1-550
Descricao: Dado uma DAG encontra o menor número de
caminhos necessários para cobrir todos os vértices.
Cada vértice é coberto exatamente uma vez. 
%*/

#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXNDAG 130
#define MAXN 2*MAXNDAG

/* BPM AQUI */

/* FILL ME */
int n;
vector<int> dag[MAXNDAG];

int minpcover() {
  memset(nadj, 0, sizeof(nadj));
  nU = nV = n;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < (int) dag[i].size(); j++) {
      int v = dag[i][j];
      adj[i][nadj[i]++] = v+n;
      adj[v+n][nadj[v+n]++] = i; 
    }
  }

  return n - maxbpm();
}

/* Abaixo apenas se for necessário imprimir a solução*/
vector<int> path[MAXNDAG];

void DFS(int u, int c) {
  path[c].push_back(u);
  if (conj[u+n] == -1) return;
  DFS(conj[u+n], c);
}       

int getPaths() {
  int res = 0;
  for (int i = 0; i < n; i++) {
    if (conj[i] == -1) {
      path[res].clear();
      DFS(i, res);
      reverse(path[res].begin(), path[res].end());
      res++;
    }
  }
  return res;
}

/**** Exemplo simples de uso ****/
int main() {    
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    dag[i].clear();
    int d;
    scanf("%d", &d);
    for (int j = 0; j < d; j++) {
      int v;
      scanf("%d", &v);
      v--;
      dag[i].push_back(v);
    }
  }

  int res = minpcover();
  getPaths();
  printf("%d\n", res);

  for (int i = 0; i < res; i++) {
    for (int j = 0; j < (int) path[i].size(); j++) {
      printf("%d ", path[i][j] + 1);
    }
    printf("\n");
  }
  return 0;
}
