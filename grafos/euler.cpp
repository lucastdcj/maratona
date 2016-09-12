/*%
Circuito e Passeio de Euler
Autor: Marcelo Galvão Póvoa
Complexidade: O(n+m)
Testes: uva.10054, codeforces.267B
Descricao: Verifica se há e encontra um circuito/passeio
de Euler em grafo não-direcionado contendo todas arestas
podendo ser paralelas ou laços e o grafo conexo ou não
%*/

#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;
#define MAXM 100100
#define MAXN 100100

/* FILL ME */
int ea[MAXM], eb[MAXM], n, m;

vector<int> vtour; // resposta: lista de vértices
vector<int> g[MAXN];
int mrk[MAXM];

/* Retorna 1 se há circuito, 2 se há passeio ou 0 c.c */
int euler() {
  for (int i=0; i<n; i++) g[i].clear();
  
  for (int i=0; i<m; i++) {
    g[ea[i]].push_back(i);
    g[eb[i]].push_back(i);
    mrk[i] = 0;
  }

  int qi = 0, v0;
  for (int i=0; i<n; i++) {
    if (!qi && g[i].size()) v0 = i;
    if (g[i].size() % 2) v0 = i, qi++;
  }
  
  if (qi > 2) return 0;

  stack<int> st;
  st.push(v0);

  vtour.clear();
  while (!st.empty()) {
    int v = st.top();

    while (g[v].size() && mrk[g[v].back()]++)
      g[v].pop_back();

    if (g[v].empty()) {
      vtour.push_back(v);
      st.pop();
    }
    else {
      int k = g[v].back();
      st.push(v == ea[k] ? eb[k] : ea[k]);
    }
  }

  return (vtour.size() == m+1) ? (1+qi/2) : 0;
}

/**** Exemplo simples de uso ****/
int main() {
  scanf("%d%d",&n,&m);

  for (int i=0; i<m; i++)
    scanf("%d%d",&ea[i],&eb[i]);

  int p = euler();
  if (!p) printf("No tour\n");
  else {
    printf("%s\n", p==2 ? "Path" : "Tour");
    
    for (int i=0; i<vtour.size(); i++)
      printf("%d ",vtour[i]);
    printf("\n");
  }
}
