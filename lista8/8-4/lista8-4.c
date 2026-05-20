#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int cod; char nome[64]; int qtd; double preco; } Prod;
typedef struct { int cod; char tipo; int qtd; } Mov;
typedef struct { int cod; char tipo; int qtd; char motivo[32]; } Inc;

static int acha(Prod *p, int n, int cod) {
    for (int i = 0; i < n; i++) if (p[i].cod == cod) return i;
    return -1;
}

int main(void) {
    FILE *fp;

    /* lê produtos */
    fp = fopen("produtos.txt", "r");
    if (!fp) { puts("Erro ao abrir arquivo."); return 1; }
    int cp = 4, np = 0;
    Prod *p = malloc(cp * sizeof(Prod));
    while (fscanf(fp, "%d %63s %d %lf", &p[np].cod, p[np].nome, &p[np].qtd, &p[np].preco) == 4) {
        if (++np == cp) p = realloc(p, (cp *= 2) * sizeof(Prod));
    }
    fclose(fp);

    /* lê movimentos */
    fp = fopen("movimentos.txt", "r");
    if (!fp) { puts("Erro ao abrir arquivo."); free(p); return 1; }
    int cm = 4, nm = 0;
    Mov *m = malloc(cm * sizeof(Mov));
    while (fscanf(fp, "%d %c %d", &m[nm].cod, &m[nm].tipo, &m[nm].qtd) == 3) {
        if (++nm == cm) m = realloc(m, (cm *= 2) * sizeof(Mov));
    }
    fclose(fp);

    /* processa */
    int aplicados = 0, recusados = 0, sem_cad = 0;
    int ci = 4, ni = 0;
    Inc *inc = malloc(ci * sizeof(Inc));

    for (int i = 0; i < nm; i++) {
        int idx = acha(p, np, m[i].cod);
        Inc tmp = {m[i].cod, m[i].tipo, m[i].qtd};

        if (idx < 0) {
            sem_cad++;
            strcpy(tmp.motivo, "PRODUTO_INEXISTENTE");
        } else if (m[i].tipo == 'E') {
            p[idx].qtd += m[i].qtd;
            aplicados++;
            continue;
        } else if (p[idx].qtd >= m[i].qtd) {
            p[idx].qtd -= m[i].qtd;
            aplicados++;
            continue;
        } else {
            recusados++;
            strcpy(tmp.motivo, "ESTOQUE_INSUFICIENTE");
        }

        if (ni == ci) inc = realloc(inc, (ci *= 2) * sizeof(Inc));
        inc[ni++] = tmp;
    }

    /* estoque_atualizado.txt */
    fp = fopen("estoque_atualizado.txt", "w");
    for (int i = 0; i < np; i++)
        fprintf(fp, "%d %s %d %.2f\n", p[i].cod, p[i].nome, p[i].qtd, p[i].preco);
    fclose(fp);

    /* relatorio.txt */
    fp = fopen("relatorio.txt", "w");
    fprintf(fp, "PRODUTOS PROCESSADOS: %d\nMOVIMENTOS APLICADOS: %d\n"
                "SAIDAS RECUSADAS: %d\nMOVIMENTOS SEM CADASTRO: %d\n",
            np, aplicados, recusados, sem_cad);
    fprintf(fp, "ESTOQUE BAIXO:\n");
    for (int i = 0; i < np; i++)
        if (p[i].qtd <= 5) fprintf(fp, "%d %s %d\n", p[i].cod, p[i].nome, p[i].qtd);
    fprintf(fp, "INCONSISTENCIAS:\n");
    for (int i = 0; i < ni; i++)
        fprintf(fp, "%d %c %d %s\n", inc[i].cod, inc[i].tipo, inc[i].qtd, inc[i].motivo);
    fclose(fp);

    free(p); free(m); free(inc);
}
