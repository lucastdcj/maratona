/*%
Operações com Frações
Autor: Davi Costa
Tempo de implementacao: 7min
Testes:  uva-10808, uva-684
Descricao: Realiza todas as operacoes com
  numeros racionais menos MOD. Eh fortem-
  ente aconselhavel usar fra<long long>
  A fracao eh sempre irredutivel e o 
  denominador eh sempre positivo.
%*/

#define ABS(x) (x < (typeof(x))0 ? -x : x)
#define F fra<T>

template<class T>
class fra {
public:
  T n,d;
  T gcds(const T &a, const T &b) const {
    if (b == T(0)) return a;
    return gcds(b,a%b);
  }
  T gcd(T a, T b) const {
    a = ABS(a); b = ABS(b);
    if (a < b) return gcds(b,a);
    return gcds(a,b);
  }
  fra(): n(T(0)), d(T(1)) {}
  fra(T num, T den = 1): n(num), d(den) {
    if (d < T(0)) d=-d, n=-n;
    T g = gcd(n,d); n /= g; d /= g;
  }
  F operator+(const F &f) const {
    // + rapido + overflow descomente a linha abaixo
    //return F(n*f.d + f.n*d,d*f.d);
    T g = gcd(d,f.d);
    return F(f.d/g*n + d/g*f.n,d/g*f.d);
  }
  F operator-() const { return F(-n,d); }
  F operator-(const F &f) const { return -f + *this; }
  F operator*(const F &f) const {
    // + rapido + overflow descomente a linha abaixo
    //return F(n*f.n,d*f.d);
    F f1(n,f.d), f2(f.n,d);
    return F(f1.n*f2.n,f1.d*f2.d);
  }
  F operator/(const F &f) const { return *this*F(f.d,f.n); }
  
  F &operator+=(const F &f){ *this = *this+f; return *this; }
  F &operator-=(const F &f){ *this = *this-f; return *this; }
  F &operator*=(const F &f){ *this = *this*f; return *this; }
  F &operator/=(const F &f){ *this = *this/f; return *this; }
  
  bool operator==(const F &f) const {return n==f.n && d==f.d;}
  bool operator!=(const F &f) const {return n!=f.n || d!=f.d;}
  bool operator< (const F &f) const {return (*this-f).n<T(0);}
  bool operator> (const F &f) const {return f < *this;}
};

/*** Exemplo simples de uso ***/
typedef fra<long long> fll;

int main() {
  fll f1= 3;
  fll f2(2,3);
  fll f3 = f1/f2;
  long long numerador = f3.n;
  long long denominador = f3.d;
  return 0;
}
