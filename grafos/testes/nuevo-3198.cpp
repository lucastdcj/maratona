#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>

using namespace std;

typedef pair<int,int> ii;

#define FOR(i,n) for(int i = 0; i < n; i++)

#define INF 0x3f3f3f3f

struct edge {
  int from,to;
  int cap,cost,x;
  edge(int from, int to, int cap, int cost):
    from(from),to(to),cap(cap),cost(cost),x(0) {};
  edge() {};
};

#define MAXN 210

edge ve[MAXN*MAXN];
int adj[MAXN][MAXN], nadj[MAXN];
int pai[MAXN], dist[MAXN], pot[MAXN], used[MAXN];
int n,m;

int dijkstra(int s) {
  memset(dist,INF,sizeof(dist));
  memset(used,0,sizeof(used));
  dist[s] = 0;
  pai[s] = -1;
  priority_queue<ii> q;
  q.push(ii(0,s));
  while (!q.empty()) {
    int v = q.top().second; q.pop();
    if (used[v]) continue;
    used[v] = true;
    FOR(i,nadj[v]) {
      edge &e = ve[adj[v][i]];
      //normal
      if (e.from == v && e.x < e.cap) {
        int c = dist[v] + e.cost + pot[v] - pot[e.to];
        if (c < dist[e.to]) {
          dist[e.to] = c;
          pai[e.to] = adj[v][i];
          q.push(ii(-c,e.to));
        }
      }
      else if (e.to == v && e.x > 0) {
        int c = dist[v] - e.cost + pot[v] - pot[e.from];
        if (c < dist[e.from]) {
          dist[e.from] = c;
          pai[e.from] = adj[v][i];
          q.push(ii(-c,e.from));
        }
      }
    }
  }
  return 1;
}

int mfmc(int s, int t) {
  FOR(i,m) {
    int from = ve[i].from;
    int to = ve[i].to;
    adj[from][nadj[from]++] = i;
    adj[to][nadj[to]++] = i;
  }
  memset(pot,0,sizeof(pot));
  int f,c;
  f = c = 0;
  while (dijkstra(s) && dist[t] != INF) {
    int v = t;
    int aug = INF;
    while (pai[v] != -1) {
      edge &e = ve[pai[v]];
      if (e.to == v) {
        aug = min(aug,e.cap - e.x);
        v = e.from;
      }
      else {
        aug = min(aug,e.x);
        v = e.to;
      }
    }
    f += aug;
    v = t;
    while (pai[v] != -1) {
      edge &e = ve[pai[v]];
      //normal
      if (e.to == v) {
        e.x += aug;
        c += aug*e.cost;
        v = e.from;
      }
      //opposite
      else {
        e.x -= aug;
        c -= aug*e.cost;
        v = e.to;
      }
    }
    FOR(i,n) pot[i] = min(INF,pot[i]+dist[i]);
  }
  return c;
}

int mat[35][35];
ii house[MAXN], man[MAXN];

int main() {
  int v,h;
  while (scanf("%d %d",&v,&h) == 2 && (h||v)) {
    memset(nadj,0,sizeof(nadj));
    int nh,nm;
    nh = nm = m = 0;
    char p;
    FOR(i,v) {
      FOR(j,h) {
        scanf(" %c",&p);
        if (p == 'H') house[nh++] = ii(i,j);
        else if (p == 'm') man[nm++] = ii(i,j);
      }
    }    
    n = nh + nm + 2;
    int s = n-2;
    int t = n-1;
    FOR(i,nh) ve[m++] = edge(s,i,1,0);
    FOR(i,nm) ve[m++] = edge(i+nh,t,1,0);
    FOR(i,nh) {
      FOR(j,nm) {
        ve[m++] = edge(i,nh+j,1,abs(house[i].first - man[j].first) + abs(house[i].second - man[j].second));
      }
    }
    printf("%d\n",mfmc(s,t));
  }  
  return 0;
}
