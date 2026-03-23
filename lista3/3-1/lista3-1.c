#include <stdio.h>

int main() {
    int teste, tamanhosequencia, i;
    int sequencia[100];

    scanf("%d", &teste);

    for (int j = 0; j < teste; j++) {
        scanf("%d", &tamanhosequencia);

        for (i = 0; i < tamanhosequencia; i++) {
            scanf("%d", &sequencia[i]); 
        }

        int position = -1;
        int melhortamanho = 0;

        for (i = 0; i < tamanhosequencia - 1;) {
            if (sequencia[i] > sequencia[i + 1]) {
                int inicio = i;
                while (i + 1 < tamanhosequencia && sequencia[i] > sequencia[i + 1]) {
                    i++;
                }
                int tamanhoatual = i - inicio + 1;

                if (tamanhoatual > melhortamanho) {
                    melhortamanho = tamanhoatual;
                    position = inicio;
                }
            } else {
                i++;
            }
        }
        if (position == -1) {
            printf("0\n");
        } else {
            // Localiza o fim da sequ�ncia decrescente

            printf("%d\n", melhortamanho);

            for (i = position; i < position + melhortamanho; i++) {
                printf("%d ", sequencia[i]);
            }
            printf("\n");     

            
            
        }  
    }
    return 0;
}