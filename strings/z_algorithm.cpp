/*%
Algoritmo Z
Autor: paladin8/Micael Carvalho
Complexidade: O(n)
Tempo de implementacao: 2 min
Testes: CodeForces.126B
Descricao: Encontra o tamanho do maior prefixo de S que comeca
em S[i], para todo S[i] (resultados em z[i]).
%*/

#define MAXN 1000000
using namespace std;

/** fill me **/
int z[MAXN];
char s[MAXN+1];
int n;

void run_z() {
    int L = 0, R = 0;
    for (int i = 1; i < n; i++) {
        if (i > R) {
            L = R = i;
            while (R < n && s[R-L] == s[R]) R++;
            z[i] = R-L; R--;
        } else {
            int k = i-L;
            if (z[k] < R-i+1) z[i] = z[k];
            else {
                L = i;
                while (R < n && s[R-L] == s[R]) R++;
                z[i] = R-L; R--;
            }
        }
    }
}

/**** Exemplo simples de uso ****/
int main() {
    int maxz = 0, res = 0;
    scanf(" %s", s);
    n = strlen(s);
    run_z();
    for (int i = 1; i < n; i++) {
        if (z[i] == n-i && maxz >= n-i) { res = n-i; break; }
        maxz = max(maxz, z[i]);
    }
    if(res > 0) {
        s[res] = '\0';
        printf("%s\n", s);
    } else {
        printf("Just a legend\n");
    }
}
