/*%
Split
Autor: Davi Costa
Complexidade: O(n)
Tempo de implementacao: 30s
Testes: nuevo-4427
Descricao: Divide uma sentenca utilizando delimitadores.
Delimitadores duplos sao ignorados e nunca aparece no 
vetor retornado strings vazias.
%*/

#include <cstring>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

#define pb push_back
typedef vector<string> vs;

//Espaco eh usado como padrao
vs split(string ss, string delim = " ") {
  vs buf;
  char *s = (char *)ss.c_str();
  char *d = (char *)delim.c_str();
  char *p = strtok(s,d);
  while (p) {
    buf.pb((const char *)p);
    p = strtok(0,d);
  }  
  return buf;
}

/**** Exemplo simples de uso ****/
int main() {
  char buf[1000];
  while (scanf("%[^\n]s",buf)) {
    getchar(); //Nao esquecer
    if (buf[0] == '\0') break;
    /*Usa espaço ou $ como delimitadores de palavras*/
    vs v = split(buf,"$ ");
    for (int i = 0; i < v.size(); i++)
      cout << v[i] << " ";
    cout << endl;
  }  
  return 0;
}
