#include <stdio.h>

#define TAM 10000

int seg_linha[TAM];
int seg_min[TAM];
int seg_max[TAM];
int total_segs = 0;

int adicionar_seg(int linha, int col1, int col2) {
    if (total_segs > 0 && seg_linha[total_segs - 1] == linha) {
        if (col1 < seg_min[total_segs - 1]) seg_min[total_segs - 1] = col1;
        if (col2 > seg_max[total_segs - 1]) seg_max[total_segs - 1] = col2;
    } else {
        seg_linha[total_segs] = linha;
        seg_min[total_segs]   = col1;
        seg_max[total_segs]   = col2;
        total_segs++;
    }
    return 0;
}

int main() {
    int qtd;
    scanf("%d", &qtd);

    int linha = 0, coluna = -1, valido = 1, i = 0;

    while (i < qtd && valido) {
        int passos;
        char direcao;
        scanf("%d %c", &passos, &direcao);

        if (direcao == 'D') {
            adicionar_seg(linha, coluna + 1, coluna + passos);
            coluna += passos;

        } else if (direcao == 'E') {
            if (coluna - passos < 0) {
                printf("Informacao invalida\n");
                valido = 0;
            } else {
                adicionar_seg(linha, coluna - passos, coluna - 1);
                coluna -= passos;
            }

        } else {
            int j = 1;
            while (j <= passos) {
                adicionar_seg(linha + j, coluna, coluna);
                j++;
            }
            linha += passos;
        }

        i++;
    }

    if (valido && total_segs > 0) {
        int ultima_linha = seg_linha[total_segs - 1];
        int si = 0;
        int l  = seg_linha[0];

        while (l <= ultima_linha) {
            if (si < total_segs && seg_linha[si] == l) {
                int k = 0;
                while (k < seg_min[si])  { putchar(' '); k++; }
                k = seg_min[si];
                while (k <= seg_max[si]) { putchar('.'); k++; }
                si++;
            }
            putchar('\n');
            l++;
        }
    }

    return 0;
}