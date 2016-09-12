/*%
Árvore de Sufixos
%*/
#define FOR(i,n) for(int i = 0; i < n; i++)
#define MAXL 27
#define cor(x) (str[x] - 'a'+1)

class Stree {
public:
  int n,l,r;
  Stree *ch[MAXL], *slink;
  string str;
  Stree(int i = 0, int f = 0):l(i),r(f) {
    slink = NULL;
    memset(ch,0,sizeof(ch));
  }
  ~Stree() {
    FOR(i,MAXL) if (ch[i]) delete ch[i];
  }
  void canonize(Stree *&anode, int &al, int ar) {
    Stree *next;
    while (al <= ar) {
      next = anode->ch[cor(al)];
      if (next->r - next->l > ar - al) break;
      al += next->r - next->l+1; anode = next;
    }
  }
  bool testsplit(Stree *&anode, int al,
                 int ar, char t, Stree *&mid) {
    if (al > ar) {
      mid = anode;
      return anode->ch[cor(al)] != NULL;
    }
    Stree *next = anode->ch[cor(al)];
    int p = ar - al + next->l+1;
    if (t == cor(p)) return true;
    mid = new Stree(next->l,p-1);
    next->l = p; mid->ch[cor(p)] = next;
    anode->ch[cor(al)] = mid;
    return false;
  }
  void update(Stree *&anode, int &al, int ar) {
    Stree *old = this, *mid;
    while(!testsplit(anode,al,ar-1,cor(ar),mid)) {
      mid->ch[cor(ar)] = new Stree(ar,n-1);
      if (old != this) old->slink = mid;
      old = mid; anode = anode->slink;
      canonize(anode,al,ar-1);
    }
    if (old != this) old->slink = anode;
  }
  void buildtree(string &str) {
    int al, ar; //active node
    Stree *anode = this;   
    this->str = str;
    n = str.size(); l=-1,r=-1;
    Stree dummy;
    FOR(i,MAXL) dummy.ch[i] = this;
    slink = &dummy;
    for (al = ar = 0; ar < n; ar++) {
      update(anode,al,ar);
      canonize(anode,al,ar);
    }
    memset(dummy.ch,0,sizeof(dummy.ch));
  }
};

int longest, last;
int n,m;

int dfs(Stree *t, int deep) {
  int sz = min(t->r,n-1) - t->l + 1;
  if (t->r == n && sz == 0) return 1;
  if (t->l != -1) deep += sz;
  int freq = 0;
  if (t->r == n) freq++;
  FOR(i,MAXL) {
    if (t->ch[i]) freq += dfs(t->ch[i],deep);
  }
  int start = min(n-1, t->r) - deep+2;
  if (t->l != -1 && freq >= m && (deep > longest || 
     (deep == longest && start < last))) {
    longest = deep;
    last = start;
  }
  return freq;
}

int main(int argv, char *argc[]) {
  string str;
  while(scanf("%d",&m) == 1 && m) {
    Stree t;
    cin >> str;
    reverse(str.begin(),str.end());
    str += 'a'-1;
    n = str.size()-1;
    t.buildtree(str);
    longest = last = 0;
    dfs(&t,0);
    if (longest == 0) printf("none\n");
    else printf("%d %d\n",longest,n-longest-last+1);
  }
}
