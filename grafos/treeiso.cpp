/*%
Isomorfismo de Árvores
Autor: Douglas Santos
Complexidade: O(n*logn)
Testes: uva.12489
Dependencias: Centro de Árvore
Descricao: Encontra o isomorfismo entre duas árvores
%*/

#include <queue>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define MAXN 10010
#define INF 0x3f3f3f3f

/* FILL ME */
int n;                    // número de vértices
vector<int> adj[2][MAXN]; // listas de adj das árvores

/* Tree Center AQUI */

typedef struct No {
  int v, lb, pai;
  vector<int> chld, lchld;
} No;

bool comp(No a, No b) {
  return a.lchld < b.lchld;
}

vector<No> niveis[MAXN];
int d[MAXN];

int add(int h, int v, int pai) {
  No no;
  no.v = v;
  no.lb = 0;
  no.lchld.clear();
  no.pai = pai;
  no.chld.clear();
  niveis[h].push_back(no);
  return niveis[h].size() - 1;
}

int BFS(int r1, int r2, int a, int b) {
  int h = 0;
  queue<pair<int, int> > q;
  for (int i = 0; i < n; i++) niveis[i].clear();
  for (int i = 0; i < 2*n; i++) {
    d[i] = INF;
  }
  d[r1] = 0;
  d[r2+n] = 0;
  add(0, r1, -1);
  add(0, r2, -1);
  q.push(make_pair(r1, 0));
  q.push(make_pair(r2+n, 1));
  while (!q.empty()) {
    int u = q.front().first;
    int ind = q.front().second;
    int k;
    q.pop();

    h = max(h, d[u]);

    if (u < n) k = a;
    else {
      k = b;
      u = u - n;
    }

    for (int i = 0; i < adj[k][u].size(); i++) {
      int v = adj[k][u][i];
      v = v + min(k-a, 1) * n;
      if (d[v] > d[u + min(k-a, 1) * n] + 1) {
        d[v] = d[u + min(k-a, 1) * n] + 1;
        No no;
        int tam;
        tam = add(d[v], v, ind);
        q.push(make_pair(v, tam));
      }
    }
  }
  return h;
}

bool isoR(int r1, int r2, int a, int b) {
  int h = BFS(r1, r2, a, b);

  for (int i = h-1; i >= 0; i--) {
    for (int j = 0; j < niveis[i+1].size(); j++) {
      No v = niveis[i+1][j];

      niveis[i][v.pai].lchld.push_back(v.lb);
      niveis[i][v.pai].chld.push_back(j);
    }
    sort(niveis[i].begin(), niveis[i].end(), comp);
    niveis[i][0].lb = 0;

    for (int j = 1; j < niveis[i].size(); j++)
      if (niveis[i][j].lchld == niveis[i][j-1].lchld) {
        niveis[i][j].lb = niveis[i][j-1].lb;
      }
      else niveis[i][j].lb = niveis[i][j-1].lb + 1;
  }
  if (niveis[0][0].lb == niveis[0][1].lb) return true;
  return false;
}

/* Retorna true se existe um isomorfismo entre
as arvores de índice a e b, a < b*/
bool isoTree(int a, int b) {
  pair<int, int> c1, c2;
  c1 = cTree(n, adj[a]);
  c2 = cTree(n, adj[b]);
  if (isoR(c1.first, c2.first, a, b)) return true;
  if (c2.second != -1)
    return isoR(c1.first, c2.second, a, b);
  return false;
}

/**** Exemplo simples de uso ****/
int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    adj[0][i].clear();
    adj[1][i].clear();
  }
  int u, v;
  for (int k = 0; k < 2; k++) {
    for (int i = 0; i < n-1; i++) {
      scanf("%d %d", &u, &v);
      u--; v--;
      adj[k][u].push_back(v);
      adj[k][v].push_back(u);
    }
  }
  if (isoTree(0, 1)) printf("S\n");
  else printf("N\n");
  return 0;
}
