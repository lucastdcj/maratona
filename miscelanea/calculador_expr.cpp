/*%
Calculador de Expressões
Autor: Alexandre Kunieda
Complexidade: O(n)
Tempo de implementacao: 4 minutos
Testes: 
- SPOJbr Calculadora (n<=?) t=0.00s
Descricao: 
Calcula expressoes que envolvam parenteses e operacoes
binarias de +, -, *, /, alem de operacao unaria de -
e variaveis de nome longo
%*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

/* tamanho maximo que as variaveis/numeros assumem */
#define MAXvar 10

char expr[1000];

map<string,double> val;
char seq[MAXvar];
char *l;

double solve();
double read() {
  int n;

  while(isspace(*l)) l++;
  if(*l=='-'){
    l++;
    return -read();
  }
  else if(*l=='('){
    l++;
    return solve();
  }
  else{
    sscanf(l," %[a-zA-Z0-9]%n",seq,&n);
    l+=n;
    if( isalpha(seq[0]) ) return val[ string(seq) ];
    else return atof(seq);
  }
}
double solve(){
  char op;
  double acc=0,ult,x;

  ult=read();

  while(*l!='\0'){
    while(isspace(*l)) l++;
    op = *(l++);
    if(op==')' || op=='\0') break;

    x = read();

    if (op=='+') { acc+=ult; ult=x; }
    if (op=='-') { acc+=ult; ult=-x; }
    if (op=='*') ult*=x;
    if (op=='/') ult/=x;
  }

  return acc+ult;
}

/**** Exemplo de uso ****/
int main(){
  int i;

  while(gets(expr)!=NULL){
    /* busca por um caracter '=' na string expr[] */
    for(i=0 ; expr[i]!='\0' && expr[i]!='=' ; i++);

    /* caso tenha achado caracter '=', seta a variavel */
    if(expr[i]=='='){
      l=expr+i+1; expr[i]='\0';
      val[ string(expr) ]=solve();
    }
    /* senao, apenas calcula a expressao */
    else{
      l = expr;
      printf("%.2lf\n", solve());
    }
  }

  return 0;
}
