/*%
Rope (via árvore cartesiana)
Autor: Marcelo Galvão Póvoa
Complexidade: O(lg n) por operação
Tempo de implementacao: ?
Testes: LiveArchive.5902
Descricao: Estrutura para manipular cadeias, suporta merge
e split em qualquer ponto. Implementada com árvore cartesiana
com Y's aleatórios, o que a torna balanceada.
%*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 100100
using namespace std;

struct _node {
  int c;      // Contagem de nós na subárvore (inclui raiz)
  int v, sum; // "Valor" da raiz e a soma deles na subárvore
  int id;     // Índice do nó na cadeia original
  int y;
  _node *l,*r;
} mem[MAXN], nil;

typedef _node* node;

// Atualiza o nó T dado que seus filhos já o fizeram
// pode ser extendido se houver outras variáveis de interesse
void fix(node T) {
  T->sum = T->v+T->l->sum+T->r->sum;
  T->c = 1+T->l->c+T->r->c;
}

// Divide subárvore T em [L,R], deixando L com x elementos
void split(node T, int x, node &L, node &R) {
  if (T==&nil) L = R = &nil;
  else if (x <= T->l->c) {
    split(T->l, x, L, T->l);
    fix(T);
    R = T;
  }
  else {
    split(T->r, x-T->l->c-1, T->r, R);
    fix(T);
    L = T;
  }
}

node merge(node L, node R) {
  if (L == &nil) return R;
  if (R == &nil) return L;
  if (L->y > R->y) {
    L->r = merge(L->r, R);
    fix(L);
    return L;
  }
  R->l = merge(L, R->l);
  fix(R);
  return R;
}

node add(node T, node N) {
  if (T == &nil) return N;
  if (T->y < N->y) {
    split(T, N->id, N->l, N->r);
    fix(N);
    return N;
  }
  if (N->id < T->id) T->l = add(T->l,N);
  else T->r = add(T->r,N);
  
  fix(T);
  return T;
}

// Uso como árvore de segmentos da variável sum
int query(node T, int ll, int rr, int a, int b) {
  if (T == &nil || a > b) return 0;
  if (a == ll && b == rr) return T->sum;
  
  int me = ll+T->l->c;
  int res = query(T->l, ll, me-1, a, min(b, me-1))+
            query(T->r, me+1, rr, max(a, me+1), b);
       
  if (a<=me && b>=me) res += T->v;

  return res;
}

// Devolve o nó na x-ésima posição de T
node getid(node T, int x) {
  if (T->l->c == x) return T;
  if (T->l->c > x) return getid(T->l, x);
  return getid(T->r, x-T->l->c-1);
}

int main() {
  int n,x;
  
  while (scanf(" %d",&n)==1 && n) {
    node t = &nil;

    for (int i=0; i<n; i++) {
      scanf(" %d",&x);

      mem[i].y=rand()%123456789;
      mem[i].v=mem[i].sum=x;
      mem[i].c=1;
      mem[i].l=mem[i].r=&nil;
      mem[i].id=i;

      t=add(t, &mem[i]);
    }

    // troca de ordem as duas metades da sequência
    node p1, p2;
    split(t, n/2, p1, p2);
    t=merge(p2, p1);

    for (int i=0; i<n; i++)
      printf("%d\n",getid(t, i)->v);
  }
  return 0;
}
