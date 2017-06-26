// Problems:
// http://codeforces.com/blog/entry/50428
// https://www.hackerrank.com/contests/w33/challenges/bonnie-and-clyde
// Theory:
// http://compalg.inf.elte.hu/~tony/Oktatas/TDK/FINAL/Chap%205.PDF
// Code:

int nb;
vector<int> adj_b[MAXN];
int id[MAXN];

void build_tree() {
  nb = 0;
  for (int u = 0; u < n; u++) {
    if (is_art[u]) id[u] = nb++;
  }  

  for (int i = 0; i < ncomp; i++) {
    int c = nb++;
    for (int u : comps[i]) {
      if (!is_art[u]) id[u] = c;
      else {            
        adj_b[c].push_back(id[u]);
        adj_b[id[u]].push_back(c);
      }
    }
  }  
  for (int i = 0; i < nb; i++) {
    sort(adj_b[i].begin(), adj_b[i].end());
    adj_b[i].erase(unique(adj_b[i].begin(), adj_b[i].end()), adj_b[i].end());
  }
}
