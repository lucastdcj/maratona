/*%
  Estrutura de Polinômio
  Autor: Alexandre Kunieda/Marcelo Póvoa
  Testes: uva.10719, uva.10326, nuevo.4460
  Descricao: Estrutura e operações com polinômios
%*/

#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

const double EPS = 1e-8;

typedef vector<double> vd;

struct polin {
  vd p; // expoentes decrescentes

  polin(){}
  polin(double x) { p.push_back(x); }
  polin(vd v): p(v) { fix(); }

  int grau() { return p.size()-1; }
  double& operator [](int i) { return p[i]; }

  void fix() {
    int i;
    for(i=0; i<=grau() && fabs(p[i])<EPS; i++) ;
    p.erase(p.begin(), p.begin()+i);
  }

  polin operator + (polin &q) {
    int k = q.grau() - grau();
    polin sum = (k>0)? q : p;
    
    for(int i=sum.grau(); i>=abs(k); i--)
        sum[i] += (k>0)? p[i-k] : q[i+k];

    sum.fix();
    return sum;
  }
  polin operator - (polin &q) {
    return q*(-1) + *this;
  }
  polin operator * (double x) {
    polin prod(p);
    for(int i=0; i<=grau(); i++)
      prod.p[i] *= x;
    return prod;
  }
  polin operator * (polin &q) {
    polin prod;

    for(int i=0; i<=grau(); i++) {
      polin aux = q * p[i];
      aux.p.resize(q.grau()+p.size()-i, 0);
      prod = prod + aux;
    }
    return prod;
  }
  pair<polin,polin> operator / (polin &d) {
    polin resto(p);
    polin q;
    int g = grau(), dg = d.grau();
    for(int i=0; i<=g-dg; i++) {
      double a = resto[i] / d[0];
      for(int j=0; j<=dg; j++)
        resto[i+j] -= a*d[j];
      q.p.push_back(a);
    }

    resto.fix();
    return make_pair(q, resto);
  }
  polin operator ~ () { // derivada
    polin dp;
    int g = grau();
    for(int i=0; i<g; i++)
      dp.p.push_back(p[i] * (g-i));
    return dp;
  }

  double eval(double x) {
    double res=0, pw=1;
    for (int i=grau(); i>=0; i--, pw*=x)
      res += pw*p[i];
    return res;
  }
};

polin mdc(polin &a, polin &b) {
  if(b.grau() == -1) return a;
  polin resto = (a/b).second;
  return mdc(b, resto);
}

/**** Exemplo simples de uso ****/
#include <stdio.h>

int main(){
  vd a0(3), b0(2);
  //x^2 + 4x - 3
  a0[0] = 1;  a0[1] = 4;  a0[2] = -3;
  //2x - 1
  b0[0] = 2;  b0[1] = -1;

  polin a(a0), b(b0);
  polin x = ((a * a)/b).first;
  printf("quotient(a^2/b) =");

  if (x.grau() == -1) puts("0");
  else {
    for(int i=0 ; i<=x.grau() ; i++)
      printf(" %+.1lfx^%d", x[i], x.grau()-i);
    putchar('\n');
  }

  return 0;
}
