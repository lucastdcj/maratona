/*%
Fluxo Máximo Edmonds-Karp (Lista Adj)
Autor: Davi costa
Complexidade: O(m*F) F = fluxo maximo
Tempo de implementacao: ?
Testes: spojbr-CAVALOS uva.820 uva.10330 uva.10480
Descricao: 
  Algoritmo de Fluxo com caminhos aumentantes usando 
  lista de adjacencias para econizar memoria, porem
  eh mais devagar que o equivalente com matriz.
  Uso: para cadaaresta "e" u-v com custo c, faca
  from[e] = u; to[e] = v; cap[e] = c.
  Caso ela seja sem direcao faca capr[e] = c
  Caso ela seja direcionada faca capr[e] = 0
  Se for usar mincut() chamar maxflow() antes
%*/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

#define pb push_back
#define INF (0x3f3f3f3f)
typedef pair<int,int> ii;

#define MAXN 200

vector<int> adj[MAXN], from, to, x, cap, capr;
int nadj[MAXN], pai[MAXN], paie[MAXN];

int n,m,s,t;

int aumenta() {
  queue<ii> q;
  int u,v,e,f;
  ii a;
  memset(pai,-1,sizeof(pai));
  pai[s] = s;
  q.push(ii(s,INF));
  while(!q.empty()) {
    a = q.front(); q.pop();
    v = a.first; f = a.second;
    if (v == t) break;
    for (int i = 0; i < nadj[v]; i++) {
      e = adj[v][i];
      if (from[e] == v) { 
	u = to[e];
	if (pai[u] != -1 || x[e] == cap[e]) continue;
	q.push(ii(u,min(f,cap[e] - x[e])));
      }
      else {
	u = from[e];
	if (pai[u] != -1 || x[e] == -capr[e]) continue;
	q.push(ii(u,min(f,capr[e] + x[e])));
      }
      pai[u] = v; paie[u] = e;
    }
  }
  if (v != t) return 0;
  while (v != s) {
    e = paie[v];
    if (to[e] == v) x[e] += f;
    else x[e] -= f;
    v = pai[v];
  }
  return f;
}

int maxflow() {
  x.resize(m); fill(x.begin(),x.end(),0);
  for (int i = 0; i < n; i++) adj[i].clear();
  for (int i = 0; i < m; i++) 
    adj[from[i]].pb(i), adj[to[i]].pb(i);
  for (int i = 0; i < n; i++) nadj[i] = adj[i].size();
  int f,r=0;
  while((f = aumenta())) r += f;
  return r;
}

/* funcoes para encontar um s-t-corte minimo */
int mark[MAXN];
vector<int> cut;

void dfs(int u) {
  mark[u] = 1;
  for (int i = 0; i < nadj[u]; i++) {
    int e = adj[u][i], v = (from[e] == u ? to[e] : from[e]);
    if (!mark[v] && (x[e] < cap[e] && x[e] > -capr[e]))
      dfs(v);
  }
}

void mincut() {
  memset(mark,0,sizeof(pai));
  cut.clear();
  dfs(s);
  for (int i = 0; i < n; i++)
    if (mark[i])
      for (int j = 0; j < nadj[i]; j++) {
	int e = adj[i][j], v = (from[e] == i ? to[e] : from[e]);
	if (!mark[v]) cut.pb(e);
      }
}

/*** Exemplo simples de uso ***/
int main() {
  int i;
  while(scanf("%d%d", &n, &m) == 2 && (n || m) {
    from.resize(m); to.resize(m); cap.resize(m); capr.resize(m);
    for (i = 0; i < m; i++) {
      int u, v, c;
      scanf("%d%d%d", &u, &v, &c);
      from[i] = u; to[i] = v; cap[i] = c; capr[i] = c;
    }
    s = 0; t = 1;
    printf("Fluxo Maximo: %d",maxflow());
    mincut();
    printf("Extremos das arestas de corte:\n")
    for (int i = 0; i < (int)cut.size(); i++)
      printf("%d %d\n",from[cut[i]],to[cut[i]]);
    printf("\n");
  }
  return 0;
}
