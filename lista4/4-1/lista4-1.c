#include <stdio.h>
#include <string.h>

int main() {
    int linhas, colunas;
    scanf("%dx%d", &linhas, &colunas);

    char grid[105][105];
    for (int i = 0; i < linhas; i++) scanf("%s", grid[i]);

    // Fila BFS
    int filaR[100000], filaC[100000], filaDist[100000];
    int head = 0, cauda = 0;
    int visitado[105][105] = {0};

    // Acha origem
    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            if (grid[i][j] == 'o') {
                filaR[cauda] = i;
                filaC[cauda] = j;
                filaDist[cauda] = 0;
                cauda++;
                visitado[i][j] = 1;
            }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (head < cauda) {
        int r    = filaR[head];
        int c    = filaC[head];
        int dist = filaDist[head];
        head++;

        if (grid[r][c] == 'd') {
            printf("Apos correr %d metros e quase desistir por causa da dist�ncia, Rebeka conseguiu escapar!\n", dist);
            return 0;
        }

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 0 || nr >= linhas || nc < 0 || nc >= colunas) continue;
            if (visitado[nr][nc]) continue;
            if (grid[nr][nc] == '#') continue;
            visitado[nr][nc] = 1;
            filaR[cauda]    = nr;
            filaC[cauda]    = nc;
            filaDist[cauda] = dist + 1;
            cauda++;
        }
    }

    printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n");
    return 0;
}