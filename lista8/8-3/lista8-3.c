#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { double sl, sw, pl, pw; char esp[64]; } Iris;
typedef struct { char nome[64]; int freq; } Cont;

int main(void) {
    int qtd;
    scanf("%d", &qtd);

    for (int f = 1; f <= qtd; f++) {
        char nome[32];
        sprintf(nome, "iris%d.csv", f);

        FILE *fp = fopen(nome, "r");
        if (!fp) { fprintf(stderr, "Erro ao abrir %s\n", nome); continue; }

        char linha[256];
        fgets(linha, sizeof(linha), fp); /* pula cabeçalho */

        int cap = 4, n = 0;
        Iris *d = malloc(cap * sizeof(Iris));
        int ce = 4, ne = 0;
        Cont *c = malloc(ce * sizeof(Cont));

        while (fgets(linha, sizeof(linha), fp) && linha[0] != '#' && linha[0] != '\n') {
            Iris t;
            if (sscanf(linha, "%lf,%lf,%lf,%lf,%63[^\n]",
                       &t.sl, &t.sw, &t.pl, &t.pw, t.esp) != 5) continue;
            if (n == cap) d = realloc(d, (cap *= 2) * sizeof(Iris));
            d[n++] = t;

            int found = 0;
            for (int i = 0; i < ne; i++)
                if (!strcmp(c[i].nome, t.esp)) { c[i].freq++; found = 1; break; }
            if (!found) {
                if (ne == ce) c = realloc(c, (ce *= 2) * sizeof(Cont));
                strcpy(c[ne].nome, t.esp);
                c[ne++].freq = 1;
            }
        }
        fclose(fp);

        double sl=0, sw=0, pl=0, pw=0;
        for (int i = 0; i < n; i++) { sl+=d[i].sl; sw+=d[i].sw; pl+=d[i].pl; pw+=d[i].pw; }
        sl/=n; sw/=n; pl/=n; pw/=n;

        /* moda (desempate lexicográfico) */
        int best = -1;
        char *moda = NULL;
        for (int i = 0; i < ne; i++)
            if (c[i].freq > best || (c[i].freq == best && strcmp(c[i].nome, moda) < 0))
                { best = c[i].freq; moda = c[i].nome; }

        /* exibe conteúdo no terminal */
        printf("=== %s ===\n", nome);
        fp = fopen(nome, "r");
        while (fgets(linha, sizeof(linha), fp)) printf("%s", linha);
        fclose(fp);

        /* grava resultados */
        fp = fopen(nome, "a");
        fprintf(fp, "\n#RESULTADOS\nmedia_sepal_length=%.2f\nmedia_sepal_width=%.2f\n"
                    "media_petal_length=%.2f\nmedia_petal_width=%.2f\nespecie_predominante=%s\n",
                sl, sw, pl, pw, moda);
        fclose(fp);

        free(d); free(c);
    }
}
