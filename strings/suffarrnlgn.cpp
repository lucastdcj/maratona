/*%
  Array de Sufixos n*lg(n)
  Autor: Douglas Oliveira Santos
  Complexidade: O(n*lg(n))
  Testes: nuevo-4477
    Descricao: Gera o indice de cada sufixo quando ordenados
  lexicograficamente em O(n*lg(n)). No entanto, só calcula
  LCP de sufixos adjacentes.
  %*/

#include <cstring>
#include <algorithm>

using namespace std;

#define N 150000

char str[N], inp[N];
int H, Bucket[N], nBucket[N], Rank[N], Height[N], c;

struct Suffix {
  int idx; // Suffix starts at idx, i.e. it's str[ idx .. L-1 ]
  bool operator<(const Suffix& sfx) const
  // Compares two suffixes based on their first 2H symbols,
  // assuming we know the result for H symbols.
  {
    if(H == 0) return str[idx] < str[sfx.idx];
    else if(Bucket[idx] == Bucket[sfx.idx])
      return (Bucket[idx+H] < Bucket[sfx.idx+H]);
    else
      return (Bucket[idx] < Bucket[sfx.idx]);
  }
  bool operator==(const Suffix& sfx) const {
    return !(*this < sfx) && !(sfx < *this);
  }
} Pos[N];

int UpdateBuckets(int L) {
  int start = 0, id = 0, c = 0;
  for(int i = 0; i < L; i++) {
    if(i != 0 && !(Pos[i] == Pos[i-1])) {
      start = i;
      id++;
    }
    if(i != start)
      c = 1;
    nBucket[Pos[i].idx] = id;
  }
  memcpy(Bucket, nBucket, 4 * L);
  return c;
}

void SuffixSort(int L) {
  H = 0;
  for(int i = 0; i < L; i++) Pos[i].idx = i;
  sort(Pos, Pos + L);
  c = UpdateBuckets(L);
  for(H=1;c;H *= 2) {
    // Sort based on first 2*H symbols, assuming
    // that we have sorted based on first H character
    sort(Pos, Pos+L);
    // Update Buckets based on first 2*H symbols
    c = UpdateBuckets(L);
  }
}

// Must compute the suffix array Pos first
void ComputeLCP(int L) {
  for (int i = 0; i < L; i++) Rank[Pos[i].idx] = i;
  int h = 0;
  for (int i = 0; i < L; i++)
    if (Rank[i] > 0) {
      int k = Pos[Rank[i] - 1].idx;
      while (str[i+h] == str[k+h])
        ++h;
      Height[Rank[i]] = h;
      if (h > 0) --h;
    }
}

int main() {
  scanf("%s",str);

  /* e necessario colocar o tamanho + 1 */
  int n = strlen(str) + 1;
  SuffixSort(n);

  ComputeLCP(n);

  /* Pos[i].idx guarda a posicao na string original */
  for (int i = 0; i < n; i++) {
    printf("%d\n", Pos[i].idx);
  }

  /* Height[i] tem o LCP da posicao i com a posicao i-1 */
  for (int i = 0; i < n; i++) {
    printf("%d\n", Height[i]);
  }

  return 0;
}
