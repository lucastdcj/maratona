/*%
Two Satisfiability
Autor: Davi Costa
Complexidade: O(E + V)
Tempo de implementacao: ?
Testes: spoj.CARDAPIO nuevo-2886
Dependencias: SCC
Descricao: 
   Determina se existe uma atribuicao
   que satisfaca a expressao (Xi v Xk)^(Xj v !Xl)...
   Para cada clausula deve haver uma aresta
   no grafo da forma !Xi -> Xk e !Xk -> Xi
   A funcao "clau" gera as arestas automaticamente
   dada a clausula, ver exemplo.
%*/

#define N(x) (2*x + 1)
#define Y(x) (2*x)
#define NEG(x) (x%2 == 1 ? x-1 : x+1)

/*n deve ser o numero total de literais p (nao 2*p))*/
bool two_sat(int n) {
  n *= 2;
  bool ok = true;
  scc(n);
  for (int i=0; i<n/2 && ok; i++)
    ok &= (comp[2*i] != comp[2*i+1]);
  return ok;
}

/*Solucao da literal x apos rodar two_sat() == true */
int getsol(int x) {
  return comp[2*x] < comp[2*x+1];
}

/*Insira a clausula como descrito na main*/
void clau(int x, int y) {
  int negx = NEG(x), negy = NEG(y);
  adj[negx][nadj[negx]++] = y;
  adj[negy][nadj[negy]++] = x;
}

/**** Exemplo simples de uso ****/
int main() {
  /* Nunca use N e Y recursivamente, se precisar
     use NEG apos a primeira negacao ou afirmacao */
  /* Exemplo de uso, cada pessoa entra com x, y, w, z,
     sendo que x ou y deve ser atendido e w ou z nao pode */
  int k, n;
  memset(nadj,0,sizeof(nadj));
  scanf("%d %d",&k,&n);
  for (int i = 0; i < k; i++) {
    int x,y,w,z;
    scanf("%d %d %d %d",&x,&y,&w,&z);
    clau(Y(x),Y(y)); // x ou y
    clau(N(w),N(z)); // nao(w) ou nao(z)
  }
  printf("%s\n",two_sat(n)?"yes":"no");
}
