#include <iostream>
#include <queue>
#include <limits.h>
#include <math.h>

using namespace std;

#define MAXN 110 //numero maximo de vertices
#define MAXM MAXN*MAXN

int orig[MAXM]; //origem da aresta i
int dest[MAXM]; //destino da aresta i
double custo[MAXM]; //custo da aresta i
bool intree[MAXM]; //caso precise da arvore ao final
int ord[MAXM]; //auxiliar
int id[MAXN]; //uf auxiliar
int sz[MAXN]; //uf auxiliar

void ufinit(int n) {
  for (int i = 0; i < n; i++)
    id[i] = i, sz[i] = 1;
}

int uffind(int i) {
  if (i == id[i]) return i;
  return id[i] = uffind(id[i]);
}

void ufunion(int v, int w) {
  v = uffind(v); w = uffind(w);
  if (v == w) return;
  if (sz[v] > sz[w]) swap(v,w);
  id[v] = w;
  if (sz[v] == sz[w]) sz[w]++;
}

bool edgecmp(int i, int j) { 
  return (custo[i] < custo[j]);
}

double kruskal(int n, int ne) {
  double cost = 0;
  //memset(intree,0,sizeof(intree));
  for (int i = 0; i < ne; i++) ord[i] = i;
  sort(ord,&ord[ne],edgecmp);
  ufinit(n);
  int k = 0;
  for (int i = 0; i < ne && k < n; i++) {
    int v = ord[i];
    if (uffind(orig[v]) != uffind(dest[v])) {
      //intree[v] = true;
      ufunion(orig[v],dest[v]);
      cost += custo[v]; k++;
    }
  }
  return cost;
}


/**** Exemplo simples de uso ****/
int main() {
  int n, m, k;
  double cost;
  pair<double,double> v[MAXN];
  scanf("%d",&k);
  for (int z = 0; z < k; z++) {
    if (z != 0) printf("\n");
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
      scanf("%lf %lf",&v[i].first,&v[i].second);
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i+1; j < n; j++) {
	cost = pow(pow(v[i].first - v[j].first,2) + pow(v[i].second - v[j].second,2),.5);
	custo[k] = cost;
	orig[k] = i;
	dest[k] = j;
	k++;
      }
    }
    printf("%.2lf\n",kruskal(n,k));
  }
  return 0;
}
