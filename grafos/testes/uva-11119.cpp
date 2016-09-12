#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

using namespace std;

#define MAXM 212
#define MAXN 212

int m, n;
int L[MAXM][MAXN], R[MAXN][MAXM];
int L2R[MAXM], R2L[MAXN];

int p[MAXM];

void stableMarriage() {
  memset( R2L, -1, sizeof( R2L ) );
  memset( p, 0, sizeof( p ) );

  // Each man proposes...
  for( int i = 0; i < m; i++ ) {
    int man = i;
    while( man >= 0 ) {
      // to the next woman on his list in order of decreasing preference,
      // until one of them accepts;
      int wom;
      while( 1 ) {
	wom = L[man][p[man]++];
	if( R2L[wom] < 0 || R[wom][man] > R[wom][R2L[wom]] ) break;
      }

      // Remember the old husband of wom.
      int hubby = R2L[wom];

      // Marry man and wom.
      R2L[L2R[man] = wom] = man;

      // If a guy was dumped in the process, remarry him now.
      man = hubby;
    }
  }
}

int NcM[MAXM][MAXN], NaM[MAXM][MAXN];
map<string, int> dict;

char men[MAXN][20], wom[MAXM][20];

int main() {
  int Na, Nc, i, j, k, scn = 1, mxt;

  for (;;) {
    scanf("%d", &Nc);
    if (!Nc) break;
    dict.clear();
    for (i = 0; i < Nc; i++) {
      scanf(" %s", men[i]);
      dict[string(men[i])] = i;
    }
    scanf("%d", &Na);
    for (i = 0; i < Na; i++) {
      scanf(" %s", wom[i]);
      dict[string(wom[i])] = i;
    }

    for (i = 0; i < Nc; i++)
      for (j = 0; j < Na; j++) {
	scanf("%d", &NcM[i][j]);
      }
    for (i = 0; i < Na; i++)
      for (j = 0; j < Nc; j++)
	scanf("%d", &NaM[i][j]);
    
    mxt = 1;
    for (;;) {
      int u, v, t;
      char comp[20];
      vector<int> lu, lv;
      scanf("%d", &t); if (!t) break;
      for (k = 0; k < t; k++) {
	string s;
	scanf(" %s", comp); s = comp;
	u = dict[s.substr(0, 2)];
	v = dict[s.substr(2, 2)];
	lu.push_back(u);
	lv.push_back(v);
      }
      m = lu.size(); n = lv.size();
      for (i = 0; i < m; i++) {
	vector<pair<int, int> > lp;
	for (j = 0; j < n; j++) {
	  lp.push_back(make_pair(-NcM[lu[i]][lv[j]], j));
	}
	sort(lp.begin(), lp.end());
	for (j = 0; j < n; j++)
	  L[i][j] = lp[j].second;
      }
      for (i = 0; i < n; i++)
	for (j = 0; j < m; j++)
	  R[i][j] = NaM[lv[i]][lu[j]];

      stableMarriage();
      printf("Scenario %d, Mixture %d:\n", scn, mxt++);
      printf("%s%s", men[lu[0]], wom[lv[L2R[0]]]);
      for (i = 1; i < n; i++)
	printf(" %s%s", men[lu[i]], wom[lv[L2R[i]]]);
      printf("\n\n");
    }
    scn++;
  }

  return 0;
}
