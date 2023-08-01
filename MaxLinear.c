#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int V, Nulo;
} Matrix;

int main() {
  int n, m, *V, *C, *I, aux;
  Matrix **S;
  while (scanf("%d %d", &n, &m) != EOF) {
    V = (int *)malloc(n * sizeof(int));
    C = (int *)malloc(m * sizeof(int));
    I = (int *)malloc(m * sizeof(int));
    for (int a = 0; a < n; a++) {
      scanf("%d", &V[a]);
    }
    for (int a = 0; a < m; a++) {
      scanf("%d", &C[a]);
    }
    S = (Matrix **)malloc((m + 1) * sizeof(Matrix *));
    for (int a = 0; a <= m; a++) {
      S[a] = (Matrix *)malloc((n + 1) * sizeof(Matrix));
      for (int b = 0; b <= n; b++) {
        S[a][b].Nulo = 1;
        S[a][b].V = 0;
      }
    }
    for (int a = 1; a <= m; a++) {
      for (int b = 1; b <= (n - m) + a; b++) {
        if (b >= a) {
          if (S[a][b - 1].Nulo == 1) {
            if (S[a - 1][b - 1].Nulo == 1) {
              S[a][b].V = C[a - 1] * V[b - 1];
              S[a][b].Nulo = 0;
            } else {
              S[a][b].V = (C[a - 1] * V[b - 1]) + S[a - 1][b - 1].V;
              S[a][b].Nulo = 0;
            }
          } else {
            if (S[a - 1][b - 1].Nulo == 1) {
              if (S[a][b - 1].V >= C[a - 1] * V[b - 1]) {
                S[a][b].V = S[a][b - 1].V;
                S[a][b].Nulo = 0;
              } else {
                S[a][b].V = C[a - 1] * V[b - 1];
                S[a][b].Nulo = 0;
              }
            } else {
              if (S[a][b - 1].V >= (C[a - 1] * V[b - 1]) + S[a - 1][b - 1].V) {
                S[a][b].V = S[a][b - 1].V;
                S[a][b].Nulo = 0;
              } else {
                S[a][b].V = (C[a - 1] * V[b - 1]) + S[a - 1][b - 1].V;
                S[a][b].Nulo = 0;
              }
            }
          }
        }
      }
    }
    aux = m;
    for (int a = n; a >= 0; a--) {
      if (S[aux][a - 1].V != S[aux][a].V && aux != 0) {
        aux--;
        I[aux] = a - 1;
      }
    }
    printf("%d\n", S[m][n].V);
    for (int a = 0; a < m; a++) {
      if (a == m - 1) {
        printf("%d", I[a]);
      } else {
        printf("%d ", I[a]);
      }
    }
    printf("\n\n");
  }
  return 0;
}
