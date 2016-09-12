/*%
Stable Marriage
Autor: Igor Naverniouk, Igor Assis
Complexidade: O(m^2), m = numero de homens
Tempo de implementacao: ?
Testes: uva.11119
Descricao:  
    Takes a set of m men and n women, where each person has
    an integer preference for each of the persons of opposite
    sex. Produces a matching of each man to some woman.
    The matching will have the following properties:
        - Each man is assigned a different woman
          (n must be at least m).
        - No two couples M1W1 and M2W2 will be unstable.
        - The solution is man-optimal.
    Two couples are unstable if
        - M1 prefers W2 over W1 and
        - W1 prefers M2 over M1.
%*/

#include <cstring>

#define MAXM 1024
#define MAXN 1024

int m, n; // number of men and women, n>=m
// the list of women in order of decreasing preference (man i)
int L[MAXM][MAXN]; 
int R[MAXN][MAXM]; // the attractiveness of man i to woman j
int L2R[MAXM]; // the mate of man i (always between 0 and n-1)
int R2L[MAXN]; // the mate of woman j (or -1 if single)

int p[MAXM];

void stableMarriage() {
  memset( R2L, -1, sizeof( R2L ) );
  memset( p, 0, sizeof( p ) );

  // Each man proposes...
  for( int i = 0; i < m; i++ ) {
    int man = i;
    while( man >= 0 ) {
      // to the next woman on his list in order 
      // of decreasing preference, until one of them accepts;
      int wom;
      while( 1 ) {
        wom = L[man][p[man]++];
        if (R2L[wom] < 0 || R[wom][man] > R[wom][R2L[wom]])
          break;
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
