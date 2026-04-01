#include <stdio.h>

int main() {
    int matriz[4][4] = {0};
    int r = 0, c = 0;
    char mov;

    for (int i = 0; i < 20; i++) {
        scanf(" %c", &mov);
        if      (mov == 'c' && r > 0) { r--; matriz[r][c]++; }
        else if (mov == 'b' && r < 3) { r++; matriz[r][c]++; }
        else if (mov == 'e' && c > 0) { c--; matriz[r][c]++; }
        else if (mov == 'd' && c < 3) { c++; matriz[r][c]++; }
        // bateu na parede = não incrementar
    }

    int maxVal = 0, maxR = 0, maxC = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (matriz[i][j] > maxVal) {  // > para pegar o primeiro em caso de empate
                maxVal = matriz[i][j];
                maxR = i;
                maxC = j;
            }

    printf("Coordenada X: %d, Y: %d\n", maxC, maxR);
    return 0;
}