#include <stdio.h>

int main() {
    int altura, largura;
    scanf("%d %d", &altura, &largura);

    char grid[105][105];
    for (int i = 0; i < altura; i++) scanf("%s", grid[i]);

    // Fila
    int filaR[1000000], filaC[1000000];
    int head = 0, cauda = 0;
    int visitado[105][105] = {0};

    // Enfileira gotas iniciais
    for (int i = 0; i < altura; i++)
        for (int j = 0; j < largura; j++)
            if (grid[i][j] == 'o') {
                visitado[i][j] = 1;
                filaR[cauda] = i;
                filaC[cauda] = j;
                cauda++;
            }

    while (head < cauda) {
        int r = filaR[head];
        int c = filaC[head];
        head++;

        if (grid[r][c] == '#') continue;
        grid[r][c] = 'o';

        if (r + 1 >= altura) continue;

        if (grid[r+1][c] != '#') {
            // cai direto
            if (!visitado[r+1][c]) {
                visitado[r+1][c] = 1;
                filaR[cauda] = r+1;
                filaC[cauda] = c;
                cauda++;
            }
        } else {
            // espalha para esquerda
            for (int col = c - 1; col >= 0; col--) {
                grid[r][col] = 'o';
                if (r + 1 >= altura || grid[r+1][col] != '#') {
                    if (r + 1 < altura && !visitado[r+1][col]) {
                        visitado[r+1][col] = 1;
                        filaR[cauda] = r+1;
                        filaC[cauda] = col;
                        cauda++;
                    }
                    break;
                }
            }
            // espalha para direita
            for (int col = c + 1; col < largura; col++) {
                grid[r][col] = 'o';
                if (r + 1 >= altura || grid[r+1][col] != '#') {
                    if (r + 1 < altura && !visitado[r+1][col]) {
                        visitado[r+1][col] = 1;
                        filaR[cauda] = r+1;
                        filaC[cauda] = col;
                        cauda++;
                    }
                    break;
                }
            }
        }
    }

    for (int i = 0; i < altura; i++) printf("%s\n", grid[i]);
    return 0;
}