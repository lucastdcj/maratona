/*%
  Árvore de Intervalos (c/ Lazy Propagation)
  Autor: Marcelo Galvão Póvoa
  Complexidade: O(lg n) por update/query
  Testes: SPOJ.LITE, SPOJ.MULTQ3, SPOJ.GSS3
    Descricao: Modelo de segtree que deve ser adaptado ao problema
  desejado. Suporta query e update em ponto ou intervalo. O código
  abaixo representa um vetor de bits com update(a,b) sendo "toggle
  bits entre a e b" e query(a,b) "quantos bits 1 entre a e b"
  %*/

#include <algorithm>
#define MAXN 100100
using namespace std;

struct tr {
  int ql;   /* Qtd de bits 1 no intervalo */
  int sz;   /* Tam do intervalo */
  int prop; /* Qtd de updates a propagar nos filhos */
} tree[4*MAXN];

/* Aplica q vezes o update no nó t (q pode ser zero) */
void apply(tr &t, int q) {
  if (q % 2) t.ql = t.sz - t.ql;
}

/* Faz x updates (chamando acc=up=x) e retorna a query a
 * partir da sub-árvore root = [rl,rr] no intervalo [a,b]
 * Para obter apenas a query, use acc=up=0 */
int go(int root, int rl, int rr,
       int a, int b, int acc, int up) {
  /* acc = acúmulo de updates dos pais mais o up original */
  /* devemos aplicar acc updates na sub-árvore */
  tree[root].prop+=acc;

  if (a > b) { /* [a,b] não está nesse nó raiz */
    /* aplica na raiz e agenda para os filhos
     * apenas os updates dos pais (sem up) */
    tree[root].prop -= up;
    apply(tree[root], acc - up);
    return 0; /* elemento nulo */
  }
  if (rl == a && rr == b) { /* [a,b] == nó raiz */
    /* basta aplicar updates na raiz e devolvê-la
     * a propagação será feita posteriormente */
    apply(tree[root], acc);
    return tree[root].ql;
  }

  int rm = (rl + rr) / 2;
  int ls = 2*root + 1, rs = 2*root + 2;

  /* res = a combinacao das querys dos filhos (p ex soma) */
  int res = go(ls, rl, rm, a, min(b,rm), tree[root].prop, up)
  + go(rs, rm + 1, rr, max(a,rm+1), b, tree[root].prop, up);

  /* nova raiz é a combinação dos filhos atualizados */
  tree[root].ql = tree[ls].ql + tree[rs].ql;
  tree[root].prop=0; /* propagação feita na raiz */
  return res;
}

/* Inicializar árvore (ou pode usar memset se tudo for 0) */
void init(int root, int rl, int rr) {
  tree[root].ql = 0;
  tree[root].sz = rr-rl+1;
  tree[root].prop = 0;

  if (rl < rr) {
    int rm = (rl+rr) / 2;
    init(2*root+1, rl, rm);
    init(2*root+2, rm+1, rr);
  }
}

/**** Exemplo simples de uso ****/
int main() {
  int n,c;

  while (scanf("%d%d",&n,&c)==2) {
    init(0,0,n-1);
    for (int i=0; i<c; i++) {
      int op, p, q;
      scanf("%d%d%d",&op,&p,&q);
      p--; q--;
      if (!op) /* update +1 em [p,q] */
         go(0,0,n-1,p,q,1,1);
      else /* query [p,q] */
        printf("%d\n", go(0,0,n-1,p,q,0,0));
    }
  }
  return 0;
}
