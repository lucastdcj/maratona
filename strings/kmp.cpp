/*%
Busca de Strings (KMP)
Autor: NU 2/Marcelo Galvão Póvoa
Complexidade: O(n+m)
Tempo de implementacao: 3 min
Testes: SPOJ.NHAY
Descricao: Acha todas as ocorrencias do padrao p num texto t
%*/
#define MAXNP 1000

int b[MAXNP+1];

void buildb(char *p, int psize) {
    int i = 0, j = b[0] = -1;
    while(i < psize) {
        while (j >= 0 && p[i] != p[j]) j = b[j];
        b[++i] = ++j;
    }
}

void kmp(char *text, char *pattern) {
    int i = -1, j = 0, m = strlen(pattern), n = strlen(text);
    buildb(pattern, m);
    while(++i < n) {
        while (j >=0 && pattern[j] != text[i]) j = b[j];
        if (++j >= m){
            j = b[j];
            printf("Achou em %d\n", i-m+1);
        }
    }
}

/**** Exemplo simples de uso ****/
int main(){
    char p[MAXNP+1], t[100000];
    while(scanf(" %s",p)==1) {
        scanf(" %s",t);
        kmp(t, p);
    }
    return 0;
}
