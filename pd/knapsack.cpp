/*%
Mochila binária (knapsack)
Autor: Micael Carvalho
Complexidade: O(nW)
Teste: CF.248A (433/A)
Descrição: Encontra uma possível solução
para o problema da mochila binária.
%*/
#include <bits/stdc++.h>
using namespace std;

int knapsack(int W, int wt[], int val[], int n) {
   int i, w;
   int K[n+1][W+1];
   for (i = 0; i <= n; i++) {
       for (w = 0; w <= W; w++) {
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (wt[i-1] <= w)
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],
                 K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
       }
   }
   return K[n][W];
}

int main() {
    int n, i, w[100], sum;
    scanf("%d", &n);
    sum = 0;
    for(i = 0; i < n; ++i) {
        scanf("%d", &w[i]);
        sum += w[i];
    }
    sum /= 2;
    i = knapsack(sum, w, w, n); // peso = valor
    if(i == sum) { // é possível separar em 2 grupos?
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    return 0;
}
