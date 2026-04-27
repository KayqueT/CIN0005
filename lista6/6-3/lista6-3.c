#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 105

static int layer[MAX][MAX];
static int dx8[] = {-1,-1,-1,0,0,1,1,1};
static int dy8[] = {-1, 0, 1,-1,1,-1,0,1};

int **new_mat(int M, int N) {
    int **m = malloc(M * sizeof(int *));
    for (int i = 0; i < M; i++) m[i] = calloc(N, sizeof(int));
    return m;
}
int **dup_mat(int **src, int M, int N) {
    int **m = new_mat(M, N);
    for (int i = 0; i < M; i++) memcpy(m[i], src[i], N * sizeof(int));
    return m;
}
void free_mat(int **m, int M) {
    for (int i = 0; i < M; i++) free(m[i]);
    free(m);
}
void print_mat(int **m, int M, int N) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) { if (j) printf(" "); printf("%d", m[i][j]); }
        printf("\n");
    }
}

void compute_aoe(int M, int N, int x, int y) {
    for (int i = 0; i < M; i++) for (int j = 0; j < N; j++) layer[i][j] = 0;
    int ox[] = {0,-1,1,0,0}, oy[] = {0,0,0,-1,1};
    for (int k = 0; k < 5; k++) {
        int nx = x+ox[k], ny = y+oy[k];
        if (nx>=0 && nx<M && ny>=0 && ny<N) layer[nx][ny] = 1;
    }
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) if (layer[i][j] == 1)
            for (int k = 0; k < 8; k++) {
                int nx = i+dx8[k], ny = j+dy8[k];
                if (nx>=0 && nx<M && ny>=0 && ny<N && !layer[nx][ny])
                    layer[nx][ny] = 2;
            }
}

int viz_vivos(int **m, int M, int N, int i, int j) {
    int cnt = 0;
    for (int k = 0; k < 8; k++) {
        int nx = i+dx8[k], ny = j+dy8[k];
        if (nx>=0 && nx<M && ny>=0 && ny<N && m[nx][ny] > 0) cnt++;
    }
    return cnt;
}

void explosao_arcana(int **mat, int M, int N, int x, int y) {
    compute_aoe(M, N, x, y);
    int **res = dup_mat(mat, M, N);
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) if (layer[i][j]) {
            int dmg = layer[i][j] == 1 ? 50 : 25;
            res[i][j] = res[i][j] > dmg ? res[i][j]-dmg : 0;
        }
    printf("Estado do mapa após usar a Explosão Arcana:\n");
    print_mat(res, M, N);
    free_mat(res, M);
}

void nuvem_venenosa(int **mat, int M, int N, int x, int y) {
    compute_aoe(M, N, x, y);
    printf("Estado do mapa, por turno, após usar a Nuvem Venenosa:\n");
    int **cur = dup_mat(mat, M, N);
    for (int t = 0; t < 3; t++) {
        int **nxt = dup_mat(cur, M, N);
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++) if (layer[i][j]) {
                int dmg = 5 + 8 * viz_vivos(cur, M, N, i, j);
                nxt[i][j] = nxt[i][j] > dmg ? nxt[i][j]-dmg : 0;
            }
        if (t) printf("\n");
        print_mat(nxt, M, N);
        int all_dead = 1;
        for (int i = 0; i < M && all_dead; i++)
            for (int j = 0; j < N && all_dead; j++)
                if (layer[i][j] && nxt[i][j]) all_dead = 0;
        free_mat(cur, M);
        cur = nxt;
        if (all_dead) break;
    }
    free_mat(cur, M);
}

int main(void) {
    int M, N; scanf("%d %d", &M, &N);
    int **mat = new_mat(M, N);
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) scanf("%d", &mat[i][j]);
    int x, y; scanf("%d %d", &x, &y);
    char tipo[30]; scanf("%s", tipo);

    void (*attack)(int **, int, int, int, int) =
        strcmp(tipo, "EXPLOSAO_ARCANA") == 0 ? explosao_arcana : nuvem_venenosa;

    printf("Estado inicial do mapa:\n");
    print_mat(mat, M, N);
    printf("\n");
    attack(mat, M, N, x, y);
    free_mat(mat, M);
    return 0;
}