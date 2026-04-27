#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enumeração de tipos elementais
typedef enum {
    FOGO         = 0,
    AGUA         = 1,
    ELETRICIDADE = 2,
    PLANTA       = 3
} TipoElemental;

static const char *TIPO_NOME[] = {"Fogo", "Agua", "Eletricidade", "Planta"};

// Estruturas
typedef struct {
    int          id;
    char         nome[100];
    TipoElemental tipo;
    int          xp;
    int          ataque;
    int          ordem; // ordem de cadastro dentro do treinador
} Pokemon;

typedef struct {
    char     nome[100];
    char     cpf[50];
    int      idade;
    Pokemon *pokemons;
    int      num_pokemons;
    int      ordem; // ordem de cadastro global
} Treinador;

// Estado global do sistema
static Treinador *treinadores     = NULL;
static int        num_treinadores = 0;
static int        prox_ordem      = 0;

// Funções auxiliares internas

static int calcular_nivel(const Treinador *t)
{
    int nivel = 0;
    for (int i = 0; i < t->num_pokemons; i++)
        nivel += 2 * t->pokemons[i].xp + t->pokemons[i].ataque;
    return nivel;
}

static Treinador *buscar_treinador(const char *cpf)
{
    for (int i = 0; i < num_treinadores; i++)
        if (strcmp(treinadores[i].cpf, cpf) == 0)
            return &treinadores[i];
    return NULL;
}

static int cmp_pokemon(const void *a, const void *b)
{
    const Pokemon *pa = (const Pokemon *)a;
    const Pokemon *pb = (const Pokemon *)b;
    int fa = 2 * pa->xp + pa->ataque;
    int fb = 2 * pb->xp + pb->ataque;
    if (fb != fa) return fb - fa;          // maior força primeiro
    return pa->ordem - pb->ordem;          // empate: menor ordem primeiro
}

static int cmp_treinador(const void *a, const void *b)
{
    const Treinador *ta = (const Treinador *)a;
    const Treinador *tb = (const Treinador *)b;
    int na = calcular_nivel(ta);
    int nb = calcular_nivel(tb);
    if (nb != na) return nb - na;          // maior nível primeiro
    return ta->ordem - tb->ordem;          // empate: menor ordem primeiro
}

// Implementações das operações
static void op_cadastrar_treinador(char *nome, char *cpf, int idade)
{
    if (buscar_treinador(cpf) != NULL) return; // CPF duplicado: ignora 

    treinadores = realloc(treinadores,
                          (num_treinadores + 1) * sizeof(Treinador));
    Treinador *t = &treinadores[num_treinadores];
    strcpy(t->nome,  nome);
    strcpy(t->cpf,   cpf);
    t->idade        = idade;
    t->pokemons     = NULL;
    t->num_pokemons = 0;
    t->ordem        = prox_ordem++;
    num_treinadores++;
}

static void op_cadastrar_pokemon(char *cpf, int id, char *nome,
                                  int xp, int ataque, int tipo)
{
    Treinador *t = buscar_treinador(cpf);
    if (t == NULL) return;

    // ID deve ser único para este treinador
    for (int i = 0; i < t->num_pokemons; i++)
        if (t->pokemons[i].id == id) return;

    t->pokemons = realloc(t->pokemons,
                          (t->num_pokemons + 1) * sizeof(Pokemon));
    Pokemon *p  = &t->pokemons[t->num_pokemons];
    p->id       = id;
    strcpy(p->nome, nome);
    p->tipo     = (TipoElemental)tipo;
    p->xp       = xp;
    p->ataque   = ataque;
    p->ordem    = t->num_pokemons; // ordem de registro dentro do treinador 
    t->num_pokemons++;
}

static void op_listar(void)
{
    printf("Classificação atual\n");

    if (num_treinadores == 0) return;

    // Cópia rasa para ordenar sem alterar o vetor original
    Treinador *sorted = malloc(num_treinadores * sizeof(Treinador));
    memcpy(sorted, treinadores, num_treinadores * sizeof(Treinador));
    qsort(sorted, num_treinadores, sizeof(Treinador), cmp_treinador);

    for (int i = 0; i < num_treinadores; i++) {
        Treinador *t = &sorted[i];
        printf("T: %s, CPF: %s, Nivel: %d\n",
               t->nome, t->cpf, calcular_nivel(t));

        if (t->num_pokemons == 0) continue;

        Pokemon *sp = malloc(t->num_pokemons * sizeof(Pokemon));
        memcpy(sp, t->pokemons, t->num_pokemons * sizeof(Pokemon));
        qsort(sp, t->num_pokemons, sizeof(Pokemon), cmp_pokemon);

        for (int j = 0; j < t->num_pokemons; j++) {
            Pokemon *p = &sp[j];
            printf("  P: %d, %s, %d, %d, %s\n",
                   p->id, p->nome, p->xp, p->ataque, TIPO_NOME[p->tipo]);
        }
        free(sp);
    }
    free(sorted);
}

static void op_remover_treinador(char *cpf)
{
    int idx = -1;
    for (int i = 0; i < num_treinadores; i++)
        if (strcmp(treinadores[i].cpf, cpf) == 0) { idx = i; break; }
    if (idx == -1) return;

    free(treinadores[idx].pokemons);

    /* Desloca os treinadores restantes */
    for (int i = idx; i < num_treinadores - 1; i++)
        treinadores[i] = treinadores[i + 1];
    num_treinadores--;

    if (num_treinadores > 0)
        treinadores = realloc(treinadores,
                              num_treinadores * sizeof(Treinador));
    else {
        free(treinadores);
        treinadores = NULL;
    }
}

static void op_atualizar_pokemon(char *cpf, int id, char *nome,
                                  int xp, int ataque, int tipo)
{
    Treinador *t = buscar_treinador(cpf);
    if (t == NULL) return;

    for (int i = 0; i < t->num_pokemons; i++) {
        if (t->pokemons[i].id == id) {
            strcpy(t->pokemons[i].nome, nome);
            t->pokemons[i].xp     = xp;
            t->pokemons[i].ataque = ataque;
            t->pokemons[i].tipo   = (TipoElemental)tipo;
            return;
        }
    }
}

static void op_liberar(void)
{
    for (int i = 0; i < num_treinadores; i++)
        free(treinadores[i].pokemons);
    free(treinadores);
    treinadores     = NULL;
    num_treinadores = 0;
}

typedef struct {
    void (*cadastrar_treinador)(char *nome, char *cpf, int idade);
    void (*cadastrar_pokemon)  (char *cpf, int id, char *nome,
                                int xp, int ataque, int tipo);
    void (*listar)             (void);
    void (*remover_treinador)  (char *cpf);
    void (*atualizar_pokemon)  (char *cpf, int id, char *nome,
                                int xp, int ataque, int tipo);
    void (*liberar)            (void);
} Operacoes;


int main(void)
{
    Operacoes ops = {
        op_cadastrar_treinador,
        op_cadastrar_pokemon,
        op_listar,
        op_remover_treinador,
        op_atualizar_pokemon,
        op_liberar
    };

    int cmd;
    while (scanf("%d", &cmd) == 1 && cmd != 0) {
        if (cmd == 1) {
            char nome[100], cpf[50];
            int  idade;
            scanf("%s %s %d", nome, cpf, &idade);
            ops.cadastrar_treinador(nome, cpf, idade);

        } else if (cmd == 2) {
            char cpf[50], nome[100];
            int  id, xp, ataque, tipo;
            scanf("%s %d %s %d %d %d", cpf, &id, nome, &xp, &ataque, &tipo);
            ops.cadastrar_pokemon(cpf, id, nome, xp, ataque, tipo);

        } else if (cmd == 3) {
            ops.listar();

        } else if (cmd == 4) {
            char cpf[50];
            scanf("%s", cpf);
            ops.remover_treinador(cpf);

        } else if (cmd == 5) {
            char cpf[50], nome[100];
            int  id, xp, ataque, tipo;
            scanf("%s %d %s %d %d %d", cpf, &id, nome, &xp, &ataque, &tipo);
            ops.atualizar_pokemon(cpf, id, nome, xp, ataque, tipo);
        }
    }

    ops.liberar();
    return 0;
}