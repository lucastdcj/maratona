/*
 * Este arquivo possui códigos de notebooks externos, não muito bem
 * testados (ou nunca testados).
 */


/********************************************************************
* STL Utils                                                         *
********************************************************************/
//Heap with priority change ( priorities in v[] )
struct comp {
        inline bool operator() (const int i, const int j) {
                return (v[i] != v[j]) ? (v[i] < v[j]) : (i < j);
        }
};
set<int, comp> s;
s.erase(x); v[x]=new_priority; s.insert(x); //priority change
v[x] = priority; s.insert(x); //insert element
int u = *s.begin(); s.erase(*s.begin()); //remove element
#define contains(s,x) ( s.find(x) != s.end() ) //set contains element

fill(v.begin(), v.end(), key); //fills the structure with key
remove(v.begin(), v.end(), val); //removes all elements with val key
replace(v.begin(),v.end(), val, new_val);
reverse(v.begin(),v.end());
find(v.begin(), v.end(), key); //returns first iterator to key
find_if(v.begin(), v.end(), pred);//where pred is bool pred(T key)
unique(v.begin(), v.end()); //eliminates duplicates

//Map with struct
struct species { 
        char s[81]; 
};
bool operator==(const species &a, const species &b){ 
        return !strcmp(a.s, b.s); 
}
bool operator<(const species &a, const species &b){
        return strcmp(a.s, b.s) < 0; 
} 
map<species,int> cnt; 



/********************************************************************
* Flow Definitions                                                  *
********************************************************************/
#define inv(e) ((e)^0x1)
#define origin(e) dest[ inv(e) ]
#define res_cap(e) upper[e] - flow[e]
vector<int> adj[NMAX]; int dest [ 2 * MMAX ]; int flow [ 2 * MMAX ];
int cost [ 2 * MMAX ]; int upper[ 2 * MMAX ]; //upper bound capacity
int pi[NMAX]; int pot[NMAX]; int d[NMAX]; int n,m;
//Initialize with n = ...; m = 0; rep(i,n) adj[i].clear();
void add_edge( int a, int b, int up, int co ) {
  dest[m] = b; upper[m] = up; cost[m] = co;
  adj[a].push_back(m++);
  dest[m] = a; upper[m] = 0; cost[m] = -co;
  adj[b].push_back(m++);
}
/********************************************************************
* Min Cost Max Flow                                                 *
********************************************************************/
bool bellman_ford(int s) {
  rep(i,n) pot[i] = INF; pot[s] = 0;
  rep(k,n) rep(u,n) rep(i,adj[u].size()) if (res_cap(adj[u][i]) > 0)
    pot[ dest[ adj[u][i] ] ] <?= pot[ u ] + cost[ adj[u][i] ];
  rep(u,n) rep(i,adj[u].size())
    if ( ( res_cap( adj[u][i] ) > 0 ) &&
        (pot[ dest[ adj[u][i] ] ] > pot[ u ] + cost[ adj[u][i] ]) )
      return false;
  return true; //no negative cycle
}
int dijkstra( int s, int t ) {
  ii top; int u,e,v,c, dist;
  rep(i,n) { d[i] = INF; pi[i] = -1; }
  set<ii> Q; Q.insert( ii(0,s) ); d[s] = 0;
  while (!Q.empty()) {
    ii top = *Q.begin(); Q.erase(Q.begin());
    u = top.second, dist = top.first;
    rep(i, adj[u].size()) if ( res_cap( adj[u][i] ) > 0 ) {
      e = adj[u][i]; v = dest[e]; c = pot[u] + cost[e] - pot[v];
      if ( d[v] > d[u] + c ) {
        if ( d[v]!=INF ) Q.erase( Q.find( ii(d[v],v) ) );
        d[v] = d[u] + c; pi[v] = e; Q.insert( ii(d[v],v) );
      }
    }
  }
  rep(i,n) if (d[i]!=INF) pot[i] += d[i];
  return d[t];
}
void min_cost_max_flow(int s, int t, int &fflow, int &fcost)
{
  int u, pflow; fflow = fcost = 0; rep(i,m) flow[i] = 0;
  rep(i,n) pot[i] = 0; // or bellman_ford(s);
  while ( 1 ) {
    dijkstra(s,t);
    if ( pi[t] != -1 ) {
      pflow = INF;
      for (u = t; u!=s; u = origin(pi[u])) {
        pflow <?= res_cap( pi[u] );
      }
      for (u = t; u!=s; u = origin(pi[u])) {
        flow[ pi[u] ] += pflow; flow[ inv(pi[u]) ] -= pflow;
        fcost += pflow*cost[ pi[u] ];
      }
      fflow += pflow;
    }
    else return;
  }
}
