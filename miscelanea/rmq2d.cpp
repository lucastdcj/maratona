/*%
Range Minimum Query 2D
Autor: André Linhares
Complexidade: 
  inicialização: O(nm)
  atualização e consulta: log(nm)
Teste: UVA 11297
Descrição: encontra a posição do menor 
elemento de uma submatriz. A função best
pode ser adaptada para Range Maximum 
Query ou para definir um critério de desempate.
%*/

#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <algorithm>

#define pii pair<int,int>

using namespace std;

#define for_to(i,j,k) for(i=j; i<=k; ++i)

#define xm (x1+x2)/2
#define ym (y1+y2)/2

#define r0 x1,xm,y1,ym
#define r1 xm+1,x2,y1,ym
#define r2 x1,xm,ym+1,y2
#define r3 xm+1,x2,ym+1,y2

#define GO go(0,r0); go(1,r1); go(2,r2); go(3,r3);

template <class T>
struct RMQ
{
  public:
  void init(vector<vector<T> > w)
  {
    R=(int)w.size()-1, C=(int)w[0].size()-1;
    v=w;
    son.assign(1,vector<int> (4,0));
    ans.resize(1,pii(0,0));
    init(0,0,R,0,C);
  }
    
  void update(T t,int i,int j=0)
  {
    x=i, y=j;
    v[x][y]=t;
    update(0,0,R,0,C);
  }
  
  pii query(int a,int b,int c=0,int d=0)
  {
    xi=a, xf=b, yi=c, yf=d;
    ret=pii(xi,yi);
    query(0,0,R,0,C);
    return ret;
  }
    

  int R,C,x,y,xi,xf,yi,yf;
  vector<vector<int> > son;
  vector<vector<T> > v;
  vector<pii> ans;
  pii ret;
  
  pii best(pii a,pii b)
  { 
    if (v[a.first][a.second] < v[b.first][b.second]) return a;
    else if (v[a.first][a.second] > v[b.first][b.second]) 
      return b;
    return min(a,b);
  }
  
#define _go(i,a,b,c,d) if (a<=b && c<=d) \
{ son[node][i]=son.size(); son.push_back(vector<int> (4,0));\
ans.push_back(pii(a,c)); init(son[node][i],a,b,c,d); \
ans[node]=best(ans[node],ans[son[node][i]]); }  

#define go(a,b) _go(a,b)
  
  void init(int node,int x1,int x2,int y1,int y2)
  { if (x1!=x2 || y1!=y2) GO; }
    
#undef _go
#define _go(i,a,b,c,d) if (a<=x && x<=b && c<=y && y<=d) \
update(son[node][i],a,b,c,d);  if (son[node][i]) \
ans[node]=best(ans[node],ans[son[node][i]]); 
  
  void update(int node,int x1,int x2,int y1,int y2)
  { if (x1!=x2 || y1!=y2) GO; }
  
#undef _go
#define _go(i,a,b,c,d) if (son[node][i] && !(a>xf || b<xi \
|| c>yf || d<yi)) { query(son[node][i],a,b,c,d); }
  
  void query(int node,int x1,int x2,int y1,int y2)
  {
    if (x1==x2 && y1==y2 || (xi<=x1 && x2<=xf && yi<=y1 
      && y2<=yf))
    {
      ret=best(ret,ans[node]);
      return;
    }
    GO;
  }
};

RMQ<int> T1,T2;
vector<vector<int> > v1,v2;
int i,j,k,n;
int m,t,x,y,a,x1,x2,y1,y2;
char c;
int a1,a2,lixo;
pii P;

int main()
{
  scanf("%d %d",&n,&lixo);
  v1=v2=vector<vector<int> > (n,vector<int>(n));
  for_to(i,0,n-1)
    for_to(j,0,n-1)
    {
      scanf("%d",&v1[i][j]);
      v2[i][j]=-v1[i][j];
    }
  T1.init(v1);
  T2.init(v2);
  scanf("%d",&m);
  for_to(t,1,m)
  {
    scanf(" %c",&c);
    if (c=='c')
    {
      scanf("%d %d %d",&x,&y,&a);
      --x, --y;
      T1.update(a,x,y);
      T2.update(-a,x,y);
    }
    else
    {
      scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
      --x1, --x2, --y1, --y2;
      P=T1.query(x1,x2,y1,y2);
      a1=T1.v[P.first][P.second];
      P=T2.query(x1,x2,y1,y2);
      a2=-T2.v[P.first][P.second];
      printf("%d %d\n",a2,a1);
    }
  }
  return 0;
}
