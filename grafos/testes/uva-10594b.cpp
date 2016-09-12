#include <queue>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> ii;
#define FOR(i,n) for(int i = 0; i < n; i++)

#define MAXN 101
#define INF 0x3f3f3f3f3f3f3f3fLL

struct edge {
  int from,to;
  ll cap,cost,x;
  edge(int from, int to, ll cap, ll cost):
    from(from),to(to),cap(cap),cost(cost),x(0) {};
  edge() {};
};

int adj[MAXN][2*MAXN], nadj[MAXN];
edge ve[MAXN*2*MAXN];
ll dist[MAXN],pot[MAXN];
int used[MAXN],pai[MAXN];
int n,m;

ll dijkstra(int s, int t) {
  FOR(i,n) dist[i] = INF;
  memset(used,0,sizeof(used));
  dist[s] = 0; pai[s] = -1;
  priority_queue<ii> q;
  q.push(ii(0,s));
  while (!q.empty()) {
    int v = q.top().second; q.pop();
    if (used[v]) continue;
    used[v] = true;
    FOR(i,nadj[v]) {
      edge &e = ve[adj[v][i]];
      if (e.from == v && e.x < e.cap) {
        ll c = dist[v] + pot[v] - pot[e.to] + e.cost;
        if (c < dist[e.to]) {
          pai[e.to] = adj[v][i];
          dist[e.to] = c;
          q.push(ii(-c,e.to));
        }
      }
      else if (e.to == v && e.x) {
        ll c = dist[v] + pot[v] - pot[e.from] - e.cost;
        if (c < dist[e.from]) {
          pai[e.from] = adj[v][i];
          dist[e.from] = c;
          q.push(ii(-c,e.from));
        }
      }
    }
  }
  return dist[t];
}

ii mfmc(int s, int t) {
  memset(nadj,0,sizeof(nadj));
  FOR(i,m) {
    int from = ve[i].from, to = ve[i].to;
    adj[from][nadj[from]++] = i;
    adj[to][nadj[to]++] = i;
  }
  ll c = 0, f = 0;
  memset(pot,0,sizeof(pot));
  while (dijkstra(s,t) != INF) {
    int v = t;
    ll aug = INF;
    while (pai[v] != -1) {
      edge &e = ve[pai[v]];
      if (v == e.to) aug = min(aug,e.cap - e.x), v = e.from;
      else aug = min(aug,e.x), v = e.to;
    }
    v = t;
    f += aug;
    while (pai[v] != -1) {
      edge &e = ve[pai[v]];
      if (v == e.to) e.x += aug, c += aug*e.cost, v = e.from;
      else e.x -= aug, c -= aug*e.cost, v = e.to;
    }
    FOR(i,n) pot[i] = min(INF,pot[i] + dist[i]);
  }
  return ii(f,c);
}


int main() {
  int mm;
  ll qtd,lim;
  while (scanf("%d %d",&n,&mm) == 2) {
    int from,to;
    ll cost;
    n += 2;
    int s = n-2;
    int t = n-1;
    m = 0;
    FOR(i,mm) {
      scanf("%d %d %lld",&from,&to,&cost);
      from--;
      to--;
      ve[m++] = edge(from,to,0,cost);
      ve[m++] = edge(to,from,0,cost);
    }
    scanf("%lld %lld",&qtd,&lim);
    FOR(i,m) ve[i].cap = lim;

    ve[m++] = edge(s,0,qtd,0);
    ve[m++] = edge(n-3,t,qtd,0);    

    ii r = mfmc(s,t);
    
    if (r.first < qtd) printf("Impossible.\n");
    else printf("%lld\n",r.second);
  }
  return 0;
}
