/*%
  Decomposição Heavy Light
  Autor: Marcelo Galvão Póvoa
  Complexidade: O(lg n) LCA / O(lg^2 n) queries
  Testes: SPOJ.QTREE, uva.12424
  Descrição: Particiona os vértices de uma árvore em chains
  (sequência de vértices ancestrais) de modo que qualquer
  caminho usa um número logarítmico de chains, que podem ser
  incrementadas para responder queries em caminhos (ver ex.)
  %*/

#include <vector>
using namespace std;
#define MAXN 100100

vector<int> g[MAXN];
/* Vértice do topo da chain i, tam da chain i e qtd delas */
int head[MAXN], chsz[MAXN], nch;
/* Chain do vértice i e seu índice nela (cresce pra raiz) */ 
int chain[MAXN], chidx[MAXN];
/* Altura do vértice i, seu antecessor e tam da subárvore */
int depth[MAXN], pai[MAXN], size[MAXN];

/* Adiciona um vértice v no topo da chain c */
void chadd(int v, int c) {
  chidx[v] = chsz[c]++;
  chain[v] = c;
  head[c] = v;
}

/* Gera as chains e vetores associados */
void dfshl(int x) {
  size[x]=1;

  for (int i = 0; i < g[x].size(); i++) {
    int v = g[x][i];
    if (pai[x] != v) {
      depth[v] = depth[x]+1;
      pai[v] = x;
      
      dfshl(v);
      size[x] += size[v];
    }
  }

  chain[x] = -1;
  for (int i = 0; i < g[x].size(); i++)
    if (g[x][i] != pai[x] && size[g[x][i]] > size[x]/2)
      chadd(x, chain[g[x][i]]);
  
  if (chain[x] == -1) chadd(x, nch++);
}

/* Exemplo de LCA. Percorre as chains no caminho entre a e b
 Pode ser alterado para responder query usando uma estrutura
 de dados de intervalos por chain (por ex. BIT, segtree) */
int lca(int a, int b) {
  while (chain[a] != chain[b]) {
    if (depth[head[chain[a]]] > depth[head[chain[b]]])
      // query chain[a] em [chidx[a], chsz[chain[a]]-1]
      a = pai[head[chain[a]]];
    else
      // query chain[b] em [chidx[b], chsz[chain[b]]-1]
      b = pai[head[chain[b]]];
  }
    
  if (depth[a] < depth[b]) {
    // query chain[a] em [chidx[b], chidx[a]]
    return a;
  }
  // query chain[a] em [chidx[a], chidx[b]]
  return b;
}

/**** Exemplo simples de uso ****/
int main() {
  int n,m,a,b;

  while (scanf("%d%d",&n,&m)==2) {
    nch=0;
    memset(chsz,0,sizeof(chsz));
    
    for (int i=0; i<n; i++)
      g[i].clear();

    for (int i=0; i<n-1; i++) {
      scanf("%d%d",&a,&b);
      g[a].push_back(b);
      g[b].push_back(a);
    }

    dfshl(0);

    while (m--) {
      scanf("%d%d",&a,&b);
      printf("%d\n",lca(a,b));
    }
  }      
  return 0;
}
