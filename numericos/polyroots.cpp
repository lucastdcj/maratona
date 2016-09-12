/*%
Raízes de Polinômio
Autor: Crbondy/Davi Costa
Tempo de implementacao: 15~20 minutos
Testes: uva-10428 (apenas raizes reais melhor tempo), 
        nuevo-4460 (raizes complexas e reais)
        KMSL4B (Raizes complexas e rais melhor tempo)
Descricao: 
  Encontra todas as raizes reais e complexas
  de um polimio INCLUSIVE repetidas. Ver exemplo de uso
  OBS: Nao eh aconselhavel mudar o EPS
%*/

#include <math.h>
#include <stdlib.h>
#include <cstdio>

using namespace std;

#define EPS (1e-10)
#define maxiter 500
#define MAX 21 //MAXDGREE + 1

inline int cmp(double a, double b = 0){
  if(fabs(a-b)<=EPS) return 0;
  if(a<b) return -1;
  return 1;
}

int roots(double *a,int n,double *wr,double *wi) {
  double sq,b2,c,disc;
  int m,numroots;
  m = n; numroots = 0;
  while (m > 1) {
    b2 = -0.5*a[m-2]; c = a[m-1]; disc = b2*b2-c;
    if (!cmp(disc/(b2*b2+fabs(c)))) disc = 0.0;
    if (disc < 0.0) {
      sq = sqrt(-disc);
      wr[m-2] = b2; wi[m-2] = sq;
      wr[m-1] = b2; wi[m-1] = -sq;
      numroots+=2;
    }
    else {
      sq = sqrt(disc);
      wr[m-2] = fabs(b2)+sq;
      if (b2 < 0.0) wr[m-2] = -wr[m-2];
      if (wr[m-2] == 0)        wr[m-1] = 0;
      else {
        wr[m-1] = c/wr[m-2];
        numroots+=2;
      }
      wi[m-2] = wi[m-1] = 0.0;
    }
    m -= 2;
  }
  if (m == 1) {
    wr[0] = -a[0]; wi[0] = 0.0;
    numroots++;
  }
  return numroots;
}

void defl(double *a,int n,double *b,double *quad,double &err){
  double r,s,c[MAX];
  int i;
  r = quad[1]; s = quad[0];
  b[1] = a[1] - r; c[1] = b[1] - r;
  for (i=2;i<=n;i++){
    b[i] = a[i] - r * b[i-1] - s * b[i-2];
    c[i] = b[i] - r * c[i-1] - s * c[i-2];
  }
  err = fabs(b[n])+fabs(b[n-1]);
}

void find_quad(double *a,int n,double *b,
               double *quad,double &err, int &iter) {
  double c[MAX],dn,dr,ds,drn,dsn,eps,r,s;
  int i;
  c[0] = 1.0;
  r = quad[1]; s = quad[0];
  dr = 1.0; ds = 0; eps = EPS;
  iter = 1;
  while (cmp(fabs(dr)+fabs(ds))) {
    if (iter > maxiter) break;
    if ((iter % 200) == 0)eps*=10.0;
    b[1] = a[1] - r; c[1] = b[1] - r;
    for (i=2;i<=n;i++){
      b[i] = a[i] - r * b[i-1] - s * b[i-2];
      c[i] = b[i] - r * c[i-1] - s * c[i-2];
    }
    dn = c[n-1] * c[n-3] - c[n-2] * c[n-2];
    drn = b[n] * c[n-3] - b[n-1] * c[n-2];
    dsn = b[n-1] * c[n-1] - b[n] * c[n-2];
    if (!cmp(dn)) {
      if (dn < 0.0) dn = -EPS/100.;
      else dn = EPS/100.;
    }
    dr = drn / dn; ds = dsn / dn;
    r += dr; s += ds;
    iter++;
  }
  quad[0] = s; quad[1] = r;
  err = fabs(ds)+fabs(dr);
}

void diff_poly(double *a,int n,double *b) {
  double coef;
  int i;
  coef = (double)n;  b[0] = 1.0;
  for (i=1;i<n;i++) 
    b[i] = a[i]*((double)(n-i))/coef;            
}

void recurse(double *a,int n,double *b,int m,double *quad,
             double &err,int &iter) {
  double c[MAX],x[MAX], rs[2],tst;
  if (!cmp(b[m])) m--;    // this bypasses roots at zero
  if (m == 2) {
    quad[0] = b[2]; quad[1] = b[1];
    err = iter = 0;
    return;
  }
  c[0] = x[0] = 1.0;
  rs[0] = quad[0];rs[1] = quad[1];
  iter = 0;
  find_quad(b,m,c,rs,err,iter);
  tst = fabs(rs[0]-quad[0])+fabs(rs[1]-quad[1]);
  if (!cmp(err)) {
    quad[0] = rs[0]; quad[1] = rs[1];
  }
  // tst will be 'large' if we converge to wrong root
  if ((iter > 5 && tst < 1e-4) || (iter > 20 && tst < 1e-1)) {
    diff_poly(b,m,c);
    recurse(a,n,c,m-1,rs,err,iter);
    quad[0] = rs[0]; quad[1] = rs[1];
  }
}

void get_quads(double *a,int n,double *quad,double *x) {
  double b[MAX],z[MAX],err,tmp;
  int iter,i,m;
  if ((tmp = a[0]) != 1.0) {
    a[0] = 1.0;
    for (i=1;i<=n;i++) {
      a[i] /= tmp;
    }
  }
  if (n == 2) {
    x[0] = a[1]; x[1] = a[2];
    return;
  }
  else if (n == 1) {
    x[0] = a[1];
    return;
  }
  m = n;  b[0] = 1.0;
  for (i=0;i<=n;i++) 
    z[i] = a[i], x[i] = 0.0;
  do {
    if (n > m)
      quad[0] = 3.14159e-1, quad[1] = 2.78127e-1;
  loop:
    find_quad(z,m,b,quad,err,iter);
    if ((err > 1e-7) || (iter > maxiter)) {
      diff_poly(z,m,b);
      iter = 0;
      recurse(z,m,b,m-1,quad,err,iter);
    }
    defl(z,m,b,quad,err);
    //mais seguro
    if (err > 0.01) {
      quad[0] = -0.003*rand();
      quad[1] = -0.002*rand();
    }
    if (err > 1) goto loop;
    x[m-2] = quad[1]; x[m-1] = quad[0];
    m -= 2;
    for (i=0;i<=m;i++) {
      z[i] = b[i];
    }
  } while (m > 2);
  if (m == 2) x[0] = b[1], x[1] = b[2];
  else x[0] = b[1];
}

/**** Exemplo simples de uso ****/
int main() {
  //sempre precisa declarar
  double a[MAX],x[MAX],wr[MAX],wi[MAX],quad[2];
  int n = 2, numr;
  //pos 0 tem o coeficiente do grau maximo
  //que precisa ser diferente de 0
  //Polinomio 2x^2 + 0x -8 = 0
  a[0] = 2; a[1] = 0; a[2] = -8;
  //bons valores iniciais
  quad[0] = 0.271828;
  quad[1] = 0.314159;
  get_quads(a,n,quad,x);
  numr = roots(x,n,wr,wi);
  //se numr for menor que n nao encontrou todas as raizes
  printf("Raiz 0: %lf + %lfi\n",wr[0],wi[0]);
  printf("Raiz 1: %lf + %lfi\n",wr[1],wi[1]);
  return 0;
}
