#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;

#define MAXN 5000

int adj[MAXN][MAXN], nadj[MAXN];
int comp[MAXN], vis[MAXN], stck[MAXN], t, high[MAXN], num, ncomp;

void dfscc(int u) {
  int i, v;
  high[u] = vis[u] = num--;
  stck[t++] = u;
  for (i = 0; i < nadj[u]; i++) {
    v = adj[u][i];
    if (!vis[v]) {
      dfscc(v);
      high[u] = max(high[u], high[v]);
    } else if (vis[v] > vis[u] && !comp[v])
      high[u] = max(high[u], vis[v]);
  }
  if (high[u] == vis[u]) {
    ncomp++;
    do {
      v = stck[--t];
      comp[v] = ncomp;
    } while (v != u);
  }
}

void scc(int n) {
  int i;
  ncomp = t = 0; num = n;
  memset(vis, 0, sizeof(vis));
  memset(comp, 0, sizeof(comp));
  for (i = 0; i < n; i++)
    if (!vis[i])
      dfscc(i);
}

#define N(x) (2*x + 1)
#define Y(x) (2*x)
#define NEG(x) (x%2 == 1 ? x-1 : x+1)

/*n deve ser o numero total de literais p (nao 2*p))*/
bool two_sat(int n) {
  n *= 2;
  bool ok = true;
  int i;
  scc(n);
  for (i=0; i<n/2 && ok; i++)
    ok &= (comp[2*i] != comp[2*i+1]);
  return ok;
}

/*Insira a clausula como descrito na main*/
void clau(int x, int y) {
  int negx = NEG(x);
  int negy = NEG(y);
  adj[negx][nadj[negx]++] = y;
  adj[negy][nadj[negy]++] = x;
}

/**** Exemplo simples de uso ****/
#include <cstdio>

map<string, int> m;
int idfind(char s[]) {
  if (s[0] == '!') {
    s++;
  }
  if (m.find(s) == m.end()) m[s] = m.size() - 1;
  return m[s];
}

int main(void){
  int n;
  char s1[100], s2[100];
  int id1, id2;
  int k = 0;
  while (scanf("%d",&n) == 1) {
    k++;
    printf("Instancia %d\n",k);
    m.clear();
    memset(nadj,0,sizeof(nadj));
    for (int i = 0; i < n; i++) {
      scanf("%s %s",s1,s2);
      id1 = idfind(s1);
      id2 = idfind(s2);
      id1 = (s1[0] == '!' ? N(id1) : Y(id1));
      id2 = (s2[0] == '!' ? N(id2) : Y(id2));
      clau(id1,id2);
    }
    bool ok = two_sat(m.size());
    if (ok) printf("sim\n\n");
    else printf("nao\n\n");
  }
  return 0;
}
