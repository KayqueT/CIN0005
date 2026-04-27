#include <stdio.h>
#include <stdlib.h>

int **alocar(int L, int C) {
    int **mat = malloc(L * sizeof(int *));
    for (int i = 0; i < L; i++)
        mat[i] = malloc(C * sizeof(int));
    return mat;
}

void ler(int **mat, int L, int C) {
    for (int i = 0; i < L; i++)
        for (int j = 0; j < C; j++)
            scanf("%d", &mat[i][j]);
}

void imprimir(int **mat, int L, int C) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            if (j > 0) printf(" ");
            printf("%d", mat[i][j]);
        }
        printf("\n");
    }
}

void liberar(int **mat, int L) {
    for (int i = 0; i < L; i++)
        free(mat[i]);
    free(mat);
}

void aplicar(int **mat, int L, int C, int (*op)(int)) {
    for (int i = 0; i < L; i++)
        for (int j = 0; j < C; j++)
            mat[i][j] = op(mat[i][j]);
}

int dobro(int x)    { return 2 * x; }
int quadrado(int x) { return x * x; }
int absoluto(int x) { return x < 0 ? -x : x; }

int main() {
    int L, C, op;
    scanf("%d %d", &L, &C);

    int **mat = alocar(L, C);
    ler(mat, L, C);
    scanf("%d", &op);

    int (*operacao)(int);
    if      (op == 1) operacao = dobro;
    else if (op == 2) operacao = quadrado;
    else              operacao = absoluto;

    aplicar(mat, L, C, operacao);
    imprimir(mat, L, C);
    liberar(mat, L);

    return 0;
}