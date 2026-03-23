#include <stdio.h>

int main() {
    int numero, multiplos_de_x = 0, clientes_maisdeum = 0, hh, mm, z, latas = 0, vencedor = 0;
    scanf("%d", &numero);
    scanf("%d", &multiplos_de_x);
    scanf("%d", &clientes_maisdeum);

    int compras_sistema[numero + 1];

    for (int i = 0; i <= numero; i++) {
        compras_sistema[i] = 0;
    }


    for (int i = 0; i < clientes_maisdeum; i++) {
        scanf("%d:%d %d", &hh, &mm, &z);

        int min_passados = (hh - 7) * 60 + mm;
        int cliente_atual = min_passados / 3;

         if (cliente_atual <= numero) {
            compras_sistema[cliente_atual] = z;
        }
    }

    for (int j = 1; j <= numero; j++) {
        int latas_compradas = 0;

        if  (compras_sistema[j] > 0) {
            latas_compradas = compras_sistema[j];
        } else if (multiplos_de_x != 0 && j % multiplos_de_x == 0) {
            latas_compradas = 1;
        }

        latas += latas_compradas;

        if (latas >= 50 && vencedor == 0) {
            vencedor = j;
            int min_passados = j * 3; // Cada cliente leva 3 minutos para comprar uma lata
            int hh = 7 + min_passados / 60;
            int mm = min_passados % 60;

            if (latas_compradas == 1) {
                printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou 1 lata.\n", j, hh, mm);
            } else {
                printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d latas.\n", j, hh, mm, latas_compradas);
            }
            break;
        }
    }

    if (vencedor == 0) {
        int faltando_latas = 50 - latas;

    // Trata o plural do verbo "Faltar" e do substantivo "lata"
        if (faltando_latas == 1) {
            printf("Ainda nao foram vendidas latas suficientes. Falta 1 lata.\n");
        } else {
            printf("Ainda nao foram vendidas latas suficientes. Faltam %d latas.\n", faltando_latas);
        }

    }
    
    return 0;
}