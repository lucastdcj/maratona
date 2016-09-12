/*%
Operações com Matrizes
Autor: Davi Costa
Complexidade: 
  pot() - O(logn) multiplicacoes
  *, linsys, inv, det - O(n^3)
Dependencias:
  Todas as funcoes precisam da parte Obrigatoria
  pot -> *; - -> +
  lynsys -> diag, det -> diag, inv -> diag
Tempo de implementacao: 
Cada bloco Idependente ~ 3-5min, Total ~ 12min
Testes: 
  spoj-vampiros, gcj-CollectinCards, (linsys, inversa)
  uva-10808 (lynsys com racional)
  nuevo-4332(Exponenciacao modular), uva-684(Determinante)
  Soh foram feitos testes locais de sistema impossivel
Descricao: 
  Realiza diversas operacoes com matrizes
  - Modular: Descomente MOD, lembre de corrigir
  valores negativos posteriormente
  - det, inv e lynsys soh funcionam com double
  ou fracao, se usar int sera convertido tudo
  pra double antes. Se usar fracao troque 
  todos os "double" por "T" e "EPS" por "0"
  - O resolvedor de sistemas lineares seta
  duas flags no vetor resposta, mulsol indica
  multiplas solucoes e nosol indica que nao ha solucao.
  Pode-se descomentar alguns trechos abaixo para que
  caso existam multiplas solucoes o programa escolha
  valor 1.0 para algumas variaveis, porem o programa
  nao indicara se o sistema era inicialmente impossivel.
%*/

#include <iostream>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <vector>

#define FOR(i,n) for(int i=0; i<n; ++i)
#define ABS(x) (x < (typeof(x))0 ? -x : x)
#define EPS (1e-8)

using namespace std;

template<class T>
class matrix {
public:
  /*Obrigatorio*/
  int n,m,sz;
  T *data;
  double deter;
  bool nosol, mulsol;
  matrix() { n = m = sz = 0; data = NULL; }
  matrix(int n, int m): n(n), m(m) {
    sz = n*m; data = (T*)malloc(sizeof(T)*sz);
  }
  matrix(const matrix<T> &mtx){data = NULL;*this = mtx;}
  ~matrix() { free(data);}
  const matrix<T> &operator=(const matrix<T> &mtx) {
    if (&mtx == this) return *this;
    n = mtx.n; m = mtx.m; sz = mtx.sz; 
    deter = mtx.deter; nosol = mtx.nosol, mulsol = mtx.mulsol;
    data = (T*)realloc(data,sizeof(T)*sz);
    memcpy(data,mtx.data,sizeof(T)*sz);
    return *this;
  }
  T *operator[](int i) { return data + i*m; }
  void zera() { memset(data,0,sizeof(T)*sz); }
  //Fracao void zera() { FOR(i,sz) data[i] = 0; }
  /*Facilita a insercao manual de elementos*/
  void setall(T* v) { memcpy(data,v,sizeof(T)*sz); }
  void setl(int i,T* v) { memcpy(data + i*m,v,sizeof(T)*m); }
  /*Exponenciacao*/
  matrix<T> operator * (matrix<T> &mtx) {
    matrix<T> res(n,mtx.m);
    FOR(i,n) FOR(j,mtx.m) {      
        res[i][j] = 0;
        FOR(k,m)
          res[i][j] = (res[i][j]+
                       (*this)[i][k]*mtx[k][j])/*%MOD*/;
    }
    return res;
  }
  matrix<T> pot(int x) {
    matrix<T> res(n,m);
    if (x == 0) 
      FOR(i,n) FOR(j,m) res[i][j] = (i == j);
    else pot(x,res); return res;
  }
  void pot(int x, matrix<T> &res) {
    if (x == 1) { res = *this; return; }
    pot(x/2,res); res = res*res;
    if (x%2) res = res*(*this);
  }
  /*Soma e Subtracao*/
  matrix<T> operator + (matrix<T> &mtx) {
    matrix<T> res(n,m);
    FOR(i,sz) res.data[i] = (data[i] + mtx.data[i])/*%MOD*/;
    return res;
  }
  matrix<T> operator -() {
    matrix<T> res(n,m);
    FOR(i,sz) res.data[i] = -this->data[i];
    return res;
  }
  matrix<T> operator -(matrix<T> &mtx) { 
    return -mtx + *this; 
  }
  /*Transpota*/
  matrix<T> transp() {
    matrix<T> res(m,n);
    FOR(i,n) FOR(j,m) res[j][i] = (*this)[i][j];
    return res;
  }
  /*Funcao necessaria para determinante
   sistema linear e inversa*/
  matrix<double> diag(int mp = -1) {
#define M(i,j) (mat[idx[i]][j])
    matrix<double> ret(min(n,mp),m-mp), mat(n,m);
    if (mp == -1) mp = m;
    deter = 1; ret.nosol = false; ret.mulsol = false;
    FOR(i,sz) mat.data[i] = (double)data[i];
    vector<int> idx(n); FOR(i,n) idx[i]=i;
    int step=0;
    FOR(j,mp){
      int p = -1; double pivot = 0;
      for(int i=step;i<n;i++)
        if(ABS(M(i,j)) > ABS(pivot) + EPS)
          p = i, pivot = M(i,j);
      if(p==-1) {
        /*Para obemultiplas solucoes comente continue 
          e descomente as linhas abaixo */
        deter = 0; ret.mulsol = true;
        continue;
        //for(int jj = j+1; jj < m; jj++) M(step,jj) = 0.0;
        //M(step,j) = 1; M(step,m-1) = 1; p = step; pivot = 1;
      }
      if (p != step) deter *= -1, swap(idx[step],idx[p]);
      deter *= pivot;
      FOR(jj,m) M(step,jj) /= pivot;
      FOR(i,n) if (step!=i) {
        double w=M(i,j);
        FOR(k,m) M(i,k) -= w * M(step,k);
      }
      step++;
    }
    for (int i = step; i < n; i++)
      if (ABS(M(i,m))>EPS) {
        ret.nosol = true; ret.mulsol = false; break;
      }
    FOR(i,min(n,mp)) FOR(j,m-mp) ret[i][j] = M(i,j+mp);
    return ret;
#undef M
  }
  matrix<double> linsys(matrix<T> b) {
    //pra solucao viavel troque n por max(n,m) na linha abaixo
    matrix<double> msys(n,m+1);
    FOR(i,n) FOR(j,m) msys[i][j] = (double)(*this)[i][j];
    FOR(i,n) msys[i][m] = (double)b[i][0];
    for(int i = n; i < msys.n; i++) FOR(j,m+1) msys[i][j] = 0;
    return msys.diag(m);
  }
  double det() { diag(); return deter; }
  matrix<double> inv() {
    matrix<double> minv(n,2*m);
    FOR(i,n) FOR(j,m) {
      minv[i][j] = (double)(*this)[i][j];
      minv[i][j+m] = (i == j);
    }
    return minv.diag(m);
  }
};

template< class T >
ostream &operator<<( ostream &out, matrix< T > mtx ) {
  FOR(i,mtx.n) {
    FOR(j,mtx.m) {
    if(j) out << " ";
    out << mtx[i][j];
    }
    out << endl;
  }
  out << endl;
  return out;
}

typedef matrix<double> md;

int main() {
  //inicializar a matriz
  md m(2,2);
  /* 0 1
     1 2 */
  m.setall((double[]){ 0, 1, 1, 2});
  cout << m;
  /*ou*/
  m.setl(0,(double[]){ 0, 1});
  m.setl(1,(double[]){ 1, 2});
  cout << m;
  /*ou*/
  m[0][0] = 0; m[0][1] = 1; m[1][0] = 1; m[1][1] = 2;
  cout << m;
  //negacao
  md neg = -m; cout << neg;
  //soma
  md msum = m + m; cout << msum;
  //subtracao
  md msub = m - m;  cout << msub;
  //Exponenciacao
  md mpot = m.pot(15); cout << mpot;
  //identidade
  md ident = m.pot(0); cout << ident;
  //inversa
  md inv = m.inv(); cout << inv;
  //transposta
  md transp = m.transp(); cout << transp;
  //determinante
  double det = m.det(); cout << det << endl << endl;
  //sistema linear
  /* 0x + 1y = 1
     1x + 2y = -3 */
  md b(2,1);
  b.setall((double[]){ 1, -3 });
  cout << b;
  md ans = m.linsys(b);
  if (ans.mulsol) cout << "multiplas solucoes" << endl;
  if (ans.nosol) cout << "Sistema impossivel" << endl;
  cout << ans;
  /*ou sem informacoes sobre as solucoes*/
  ans = inv*b;
  cout << ans;
  double x = ans[0][0], y = ans[1][0];  
  return 0;
}
