#include <stdio.h>
#include <stdlib.h>

int quadrante_destino(int x, int y) {
    if (x > 0 && y > 0) return 1;
    if (x < 0 && y > 0) return 2;
    if (x < 0 && y < 0) return 3;
    if (x > 0 && y < 0) return 4;
    return 0; // sobre um eixo = inválido
}

int main() {
    int x, y, c;
    scanf("%d %d %d", &x, &y, &c);

    int src = quadrante_destino(x, y);
    if (src == 0) { printf("caminhada invalida\n"); return 0; }

    // Coordenadas absolutas do destino (posição (1,1) no quadrante alvo)
    int destino_x, destino_y;
    int x_primeiro_passo, y_primeiro_passo;

    if (src == 1) {
        destino_x = -1; destino_y = -1;          // Quadrante 1 → Quadrante 3
        x_primeiro_passo = 2; y_primeiro_passo = 4;

    } else if (src == 3) {
        destino_x =  1; destino_y =  1;          // Quadrante 3 → Quadrante 1
        x_primeiro_passo = 4; y_primeiro_passo = 2;
    
    } else if (src == 2) {
        destino_x =  1; destino_y = -1;          // Quadrante 2 → Quadrante 4
        x_primeiro_passo = 1; y_primeiro_passo = 3;
    
    } else {
        destino_x = -1; destino_y =  1;          // Quadrante 4 → Quadrante 2
        x_primeiro_passo = 3; y_primeiro_passo = 1;
    }

    int dx = abs(destino_x - x);
    int dy = abs(destino_y - y);

    if (c == x_primeiro_passo) {
        // Anda o y primeiro e evita o quadrante que x-primeiro passaria
        printf("%d passos em y e %d passos em x\n", dy, dx);
    } else if (c == y_primeiro_passo) {
        // Evita o quadrante que y-primeiro passaria e anda x primeiro
        printf("%d passos em x e %d passos em y\n", dx, dy);
    } else {
        printf("caminhada invalida\n");
    }

    return 0;
}