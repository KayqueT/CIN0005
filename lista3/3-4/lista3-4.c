#include <stdio.h>
#include <string.h>

int main() {
    int casos_teste;
    scanf("%d", &casos_teste);

    char resultados[1000][65];

    for (int r = 0; r < casos_teste; r++) {
        char stringleds[65];
        int flashstentados;
        scanf("%s %d", stringleds, &flashstentados);

        // Aplica flashs
        for (int f = 0; f < flashstentados; f++) {
            for (int i = 0; i < (int)strlen(stringleds); i++) {
                if (stringleds[i] == 'X') { stringleds[i] = 'O'; break; }
                else              { stringleds[i] = 'X';        }
            }
        }

        printf("%s\n", stringleds);
        strcpy(resultados[r], stringleds);
    }

    // Monta a luz gigante
    char gigante[70000];
    strcpy(gigante, resultados[0]);

    for (int i = 1; i < casos_teste; i++) {
        int  tamanho  = strlen(gigante);
        char ultimo  = gigante[tamanho - 1];
        char primeiro = resultados[i][0];
        char ornamento;

        if (tamanho % 2 == 0 &&  ultimo == primeiro) ornamento = '@';
        if (tamanho % 2 == 0 &&  ultimo != primeiro) ornamento = '$';
        if (tamanho % 2 != 0 &&  ultimo == primeiro) ornamento = '#';
        if (tamanho % 2 != 0 &&  ultimo != primeiro) ornamento = '%';

        gigante[tamanho] = ornamento;
        gigante[tamanho + 1] = '\0';
        strcat(gigante, resultados[i]);
    }

    printf("%s\n", gigante);
    return 0;
}