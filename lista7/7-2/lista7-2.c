#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Estrutura simplificada
typedef struct {
    char n[205], f[205];
    long long pop;
    int perig;
} Cid;

Cid cids[10000];
int ncids = 0;

// Comparador compactado
int cmp(const void *a, const void *b) {
    Cid *x = (Cid *)a, *y = (Cid *)b;
    if (y->pop != x->pop) return y->pop > x->pop ? 1 : -1;
    if (y->perig != x->perig) return y->perig - x->perig;
    return strcmp(x->n, y->n);
}

// Capitalização numa única linha de execução
void cap(char *s) {
    if (*s) { *s = toupper(*s); while (*++s) *s = tolower(*s); }
}

int main(void) {
    char msg[500];
    int tem_chave = 0, chave = 0;

    while (fgets(msg, sizeof(msg), stdin)) {
        Cid c = { "", "", 0, 0 };
        int nn = 0, fn = 0, esp = 0, in_w = 0;

        // 1. Extrai Nome, População, Perigo e deteta a Chave
        for (int i = 0; msg[i]; i++) {
            if (isupper(msg[i])) c.n[nn++] = msg[i];
            else if (isdigit(msg[i])) c.pop = c.pop * 10 + msg[i] - '0';
            else if (msg[i] == '*') c.perig++;
            else if (msg[i] == '!') esp = 1;
        }

        // 2. Extrai Função (Acrónimo após espaço duplo)
        char *p = strstr(msg, "  ");
        for (; p && *p; p++) {
            if (isalpha(*p)) {
                if (!in_w) c.f[fn++] = *p, in_w = 1;
            } else if (*p == ' ') in_w = 0;
            else break; // Para na pontuação
        }

        // 3. Regista a chave ou guarda a cidadela
        if (esp) { tem_chave = 1; chave = c.pop; }
        else if (nn) {
            cap(c.n); cap(c.f);
            cids[ncids++] = c;
        }
    }

    // Validação de erro
    if (!tem_chave || chave < 1 || chave > ncids) {
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
        return 0;
    }

    qsort(cids, ncids, sizeof(Cid), cmp);
    Cid *g = &cids[chave - 1];

    // Gera os asteriscos rapidamente
    char pstr[205] = "";
    memset(pstr, '*', g->perig);

    // Impressão unificada (tudo na mesma linha)
    printf("Gingrey foi encontrada em %s, uma cidadela com %lld mil habitantes cuja função é %s e periculosidade %s.",
           g->n, g->pop, g->f, pstr);

    // Condições finais na mesma linha
    if (g->pop >= 1000 && g->perig > 3) printf(" Talvez seja melhor desistir...\n");
    else if (g->pop >= 1000)            printf(" Um lugar denso, vai ser difícil achar ela.\n");
    else if (g->perig > 3)              printf(" Vai ser complicado entrar lá.\n");
    else                                printf("\n");

    return 0;
}