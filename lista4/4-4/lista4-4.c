#include <stdio.h>

int main() {
    int linhas, colunas;
    scanf("%d %d", &linhas, &colunas);

    char matriz[100][101];
    for (int i = 0; i < linhas; i++)
        scanf("%s", matriz[i]);

    char resultado[100][101];
    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            resultado[i][j] = matriz[i][j];

    // Dire��es = (+)
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // Dire��es diagonais = (x)
    int dr2[] = {-1, -1, 1, 1};
    int dc2[] = {-1, 1, -1, 1};

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == 'P') {
                // Aplica x nas diagonais
                for (int d = 0; d < 4; d++) {
                    int ni = i + dr2[d];
                    int nj = j + dc2[d];
                    if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas)
                        if (resultado[ni][nj] == '-')
                            resultado[ni][nj] = 'x';
                }
                // Aplica + nas adjacentes (prevalece sobre x)
                for (int d = 0; d < 4; d++) {
                    int ni = i + dr[d];
                    int nj = j + dc[d];
                    if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas)
                        if (resultado[ni][nj] == '-' || resultado[ni][nj] == 'x')
                            resultado[ni][nj] = '+';
                }
            }
        }
    }

    for (int i = 0; i < linhas; i++) {
        resultado[i][colunas] = '\0';
        printf("%s\n", resultado[i]);
    }

    return 0;
}