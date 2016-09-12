/*
  Emparelhamento Maximo Geral (Edmonds)
  com uma implementacao eficiente de Gabow
  Autor: Davi Costa
  Complexidade: O(n^3)
  Uso: CUIDADO - Nao utilizar o vertice 0
  - Para cada aresta 'i' (sem direcao) u-v,
    faca from[i] = u, to[i] = v e coloque i
    na lista de adjacencia de ambos u e v.
  - n e m devem ser utilizados obrigatoriamente.
  - E() retorna o tamanho do emparalhamento (# de casais).
  - mate[v] quando diferente de 0 indica que o vertice v esta
  casado com mate[v]
  Testes:
  - uva-11439
  - nuevo-4130
  - spojbr-ENGENHAR
*/

#include <iostream>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <math.h>
#include <limits.h>

using namespace std;

#define MAXN 110
#define MAXM MAXN*MAXN

int n,m;

int mate[MAXN], first[MAXN], label[MAXN];
int adj[MAXN][MAXN], nadj[MAXN], from[MAXM], to[MAXM];

queue<int> q;

#define OUTER(x) (label[x] >= 0)

void L(int x, int y, int nxy) {
  int join, v, r = first[x], s = first[y];
  if (r == s) return;
  nxy += n + 1;
  label[r] = label[s] = -nxy;
  while (1) {
    if (s != 0) swap(r,s);
    r = first[label[mate[r]]];
    if (label[r] != -nxy) label[r] = -nxy;
    else {
      join = r;
      break;
    }
  }
  v = first[x];
  while (v != join) {
    if (!OUTER(v)) q.push(v);
    label[v] = nxy; first[v] = join;
    v = first[label[mate[v]]];
  }
  v = first[y];
  while (v != join) {
    if (!OUTER(v)) q.push(v);
    label[v] = nxy; first[v] = join;
    v = first[label[mate[v]]];
  }
  for (int i = 0; i <= n; i++) {
    if (OUTER(i) && OUTER(first[i])) first[i] = join;
  }    
}

void R(int v, int w) {
  int t = mate[v]; mate[v] = w;
  if (mate[t] != v) return;
  if (label[v] >= 1 && label[v] <= n) {
    mate[t] = label[v];
    R(label[v],t);
    return;
  }
  int x = from[label[v]-n-1];
  int y = to[label[v]-n-1];
  R(x,y); R(y,x);
}

int E() {
  memset(mate,0,sizeof(mate));
  int r = 0;
  bool e7;
  for (int u = 1; u <= n; u++) {
    memset(label,-1,sizeof(label));
    while (!q.empty()) q.pop();
    if (mate[u]) continue;
    label[u] = first[u] = 0;
    q.push(u); e7 = false;
    while (!q.empty() && !e7) {
      int x = q.front(); q.pop();
      for (int i = 0; i < nadj[x]; i++) {
	int y = from[adj[x][i]];
	if (y == x) y = to[adj[x][i]];
	if (!mate[y] && y != u) {
	  mate[y] = x; R(x,y);
	  r++; e7 = true;
	  break;
	}
	else if (OUTER(y)) L(x,y,adj[x][i]);
	else {
	  int v = mate[y];
	  if (!OUTER(v)) {
	    label[v] = x; first[v] = y;
	    q.push(v);
	  }
	}
      }
    }
    label[0] = -1;
  }
  return r;
}

int main() {
  int k;
  int p;
  int t;
  scanf("%d",&k);
  for (int l = 1; l <= k; l++) {
    printf("Instancia %d\n",l);
    memset(nadj,0,sizeof(nadj));
    scanf("%d",&n);
    m = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d",&p);
      for (int j = 0; j < p; j++) {
	scanf("%d",&t);
	adj[i][nadj[i]++] = m;
	adj[t][nadj[t]++] = m;
	from[m] = i;
	to[m++] = t;
      }
    }
    if (E()*2 == n) {
      printf("pair programming\n\n");
    }
    else {
      printf("extreme programming\n\n");
    }
  }
  return 0;
}

      
