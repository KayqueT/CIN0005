#include <stdio.h>
#include <stdlib.h>

typedef int (*Filtro)(int);

int calibracao   (int v) { return v + 5; }
int saturacao    (int v) { return v > 80 ? 80 : v; }
int amplificador (int v) { return v * 2; }

Filtro filtro_por_id(int id) {
    Filtro t[] = { NULL, calibracao, saturacao, amplificador };
    return t[id];
}

void modificar(int **mat, int N, int M, Filtro *pipe, int k) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            for (int f = 0; f < k; f++)
                mat[i][j] = pipe[f](mat[i][j]);
}

int main(void) {
    int N, M;
    scanf("%d %d", &N, &M);

    int **mat = malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        mat[i] = malloc(M * sizeof(int));
        for (int j = 0; j < M; j++) scanf("%d", &mat[i][j]);
    }

    int cmd;
    while (scanf("%d", &cmd) && cmd) {
        int k;
        Filtro *pipe;
        if (cmd == 4) {
            scanf("%d", &k);
            pipe = malloc(k * sizeof(Filtro));
            for (int f = 0; f < k; f++) { int id; scanf("%d",&id); pipe[f]=filtro_por_id(id); }
        } else {
            k = 1;
            pipe = malloc(sizeof(Filtro));
            pipe[0] = filtro_por_id(cmd);
        }
        modificar(mat, N, M, pipe, k);
        free(pipe);
    }

    printf("Matriz processada:\n");
    int max = mat[0][0], li = 0, ci = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (j) printf(" ");
            printf("%d", mat[i][j]);
            if (mat[i][j] > max) { max = mat[i][j]; li = i; ci = j; }
        }
        printf("\n");
    }
    printf("\nSensor critico: %d\nPosicao: (%d,%d)\n", max, li, ci);

    for (int i = 0; i < N; i++) free(mat[i]);
    free(mat);
}