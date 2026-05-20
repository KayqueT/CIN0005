#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mecha Mecha;
typedef struct {
    char nome[30];
    int atrib1, atrib2;
    void (*subrotina)(Mecha *, int, int, int *);
} SubSistema;

struct Mecha {
    int id, energia_atual, num_sistemas, valor_wintermute;
    char modelo[50];
    SubSistema sistemas[];
};

void fn_def(Mecha *m, int s, int in, int *out) {
    int d = in - m->sistemas[s].atrib1 - s * m->sistemas[s].atrib2;
    *out = d < 0 ? 0 : d;
}
void fn_utl(Mecha *m, int s, int in, int *out) {
    (void)in;
    m->energia_atual += m->sistemas[s].atrib1 + s * m->sistemas[s].atrib2;
    *out = m->energia_atual;
}
void fn_atk(Mecha *m, int s, int in, int *out) {
    if (m->energia_atual < m->sistemas[s].atrib2) { *out = 0; return; }
    *out = m->sistemas[s].atrib1 + m->energia_atual + s - in;
    m->energia_atual -= m->sistemas[s].atrib2;
}

int cmp(const void *a, const void *b) {
    return (*(Mecha **)a)->id - (*(Mecha **)b)->id;
}

int main(void) {
    int N; scanf("%d", &N);
    Mecha **sq = malloc(N * sizeof(Mecha *));

    for (int i = 0; i < N; i++) {
        int id, e, Q; char modelo[50];
        scanf("%d %s %d %d", &id, modelo, &e, &Q);
        Mecha *m = malloc(sizeof(Mecha) + Q * sizeof(SubSistema));
        m->id = id; m->energia_atual = e; m->num_sistemas = Q;
        strcpy(m->modelo, modelo);
        for (int j = 0; j < Q; j++) {
            char t; scanf(" %c %s %d %d", &t, m->sistemas[j].nome,
                          &m->sistemas[j].atrib1, &m->sistemas[j].atrib2);
            m->sistemas[j].subrotina = t=='D' ? fn_def : t=='U' ? fn_utl : fn_atk;
        }
        scanf("%d", &m->valor_wintermute);
        sq[i] = m;
    }

    qsort(sq, N, sizeof(Mecha *), cmp);
    puts("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]");

    void (*prioridade[3])(Mecha *, int, int, int *) = {fn_def, fn_utl, fn_atk};
    const char *label[3] = {"DEFESA", "UTILIDADE", "ATAQUE"};

    for (int i = 0; i < N; i++) {
        Mecha *m = sq[i];
        printf("ID: %d | MECHA: %s | ENERGIA: %d\n", m->id, m->modelo, m->energia_atual);
        for (int p = 0; p < 3; p++)
            for (int j = 0; j < m->num_sistemas; j++)
                if (m->sistemas[j].subrotina == prioridade[p]) {
                    int out, pode = m->energia_atual >= m->sistemas[j].atrib2;
                    m->sistemas[j].subrotina(m, j, m->valor_wintermute, &out);
                    if (p == 0) printf("-> [DEFESA] %s | Dano final sofrido: %d\n",    m->sistemas[j].nome, out);
                    if (p == 1) printf("-> [UTILIDADE] %s | Energia atual: %d\n",      m->sistemas[j].nome, out);
                    if (p == 2 &&  pode) printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", m->sistemas[j].nome, out, m->energia_atual);
                    if (p == 2 && !pode) printf("-> [ATAQUE] %s | Energia insuficiente!\n", m->sistemas[j].nome);
                }
        printf("ENERGIA FINAL: %d\n-----------------------------------------\n", m->energia_atual);
        free(m);
    }

    puts("Esquadrao pronto para o combate.");
    free(sq);
}