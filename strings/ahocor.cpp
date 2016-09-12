/*%
  Aho-Corasick
  Autor: UFPE (com modificações)
  Complexidade: O(texto + padrões + ocorrências)
  Testes: liveArchive.4811
  Descrição: Dado um conjunto de padrões (strings) e um texto,
  encontra todas as ocorrências dos padrões no texto
%*/
#include <map>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int,int> pii;

/* Tamanho total dos padrões */
#define MAXST (1000100)

struct No {
  vector<pii> out; // num e tamanho do pad
  map<char, int> lis;
  int fail;
  int nxt; // aponta para o próx. sufixo com out.size > 0
};
No t[MAXST];
int qNo, qPad;

void init() {
  t[0].fail = t[0].nxt = -1;
  t[0].lis.clear();
  t[0].out.clear();
  qNo = 1;
  qPad = 0;
}

void add(const char *pad) {
  int no = 0, len = 0;
  for (int i = 0; pad[i]; i++, len++) {
    if (t[no].lis.find(pad[i]) == t[no].lis.end()) {
      t[qNo].lis.clear(); t[qNo].out.clear();
      t[no].lis[pad[i]] = qNo;
      no = qNo++;
    }
    else no = t[no].lis[pad[i]];
  }
  t[no].out.push_back(pii(qPad++, len));
}

// Ativar aho-corasick, ajustando funções de falha
void preprocess() {
  int no, v, f, w;
  queue<int> fila;
  for (map<char,int>::iterator it = t[0].lis.begin();
    it != t[0].lis.end(); it++) {
    t[no = it->second].fail = 0;
    t[no].nxt = t[0].out.size() ? 0 : -1;
    fila.push(no);
  }
  while (!fila.empty()) {
    no = fila.front(); fila.pop();
    for (map<char,int>::iterator it = t[no].lis.begin();
      it != t[no].lis.end(); it++) {
      char c = it->first;
      v = it->second;
      fila.push(v);
      f = t[no].fail;
      while (t[f].lis.find(c) == t[f].lis.end()) {
        if (f == 0) { t[0].lis[c] = 0; break; }
        f = t[f].fail;
      }
      w = t[f].lis[c];
      t[v].fail = w;
      t[v].nxt = t[w].out.size() ? w : t[w].nxt;
    }
  }
}

// descomente p/ obter só 1 ocorrência por padrão (+rápido)
// int mark[MAXST];

// Busca em text devolve pares (índice do padrão, posição)
void find(const char *text, vector<pii> &res) {
  int v, no = 0;

  // memset(mark,0,sizeof(mark));
  for (int i = 0; text[i]; i++) {
    while (t[no].lis.find(text[i]) == t[no].lis.end()) {
      if (no == 0) { t[0].lis[text[i]] = 0; break; }
      no = t[no].fail;
    }
    for (v = no = t[no].lis[text[i]]; v != -1; v = t[v].nxt) {
      // if (mark[v]++) break;
      for (int k = 0 ; k < (int)t[v].out.size() ; k++) {
        // encontrado padrao t[v].out[k].first no
        // intervalo (i-t[v].out[k].second+1)..i
        res.push_back(pii(t[v].out[k].first,
          i - t[v].out[k].second + 1));
      }
    }
  }
}

int main(){
  char text[10010], pat[10010];
  int qpat;
  
  scanf(" %s %d", text, &qpat);
  init();

  for (int i=0; i<qpat; i++) {
    scanf(" %s",pat);
    add(pat);
  }

  preprocess();
  vector<pii> oc;
  find(text, oc);

  for (int i=0; i<(int)oc.size(); i++)
    printf("Padrão %d em %d\n", oc[i].first, oc[i].second);
  return 0;
}
