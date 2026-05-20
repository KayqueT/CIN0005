#include <stdio.h>
#include <string.h>

typedef struct {
    char titulo[50], genero[50], estudio[50], console[50];
    int nota, ano;
} Jogo;

Jogo col[100];
int N;

void printAno(int ano) {
    int c = 0;
    for (int i = 0; i < N; i++)
        if (col[i].ano == ano) { printf("%s\n", col[i].titulo); c++; }
    if (c) printf("Tenho %d jogos || %d.\n", c, ano);
    else   puts("Nenhum jogo tem esse parâmetro Sr Sr Wilson.");
}

void printLetra(char l) {
    int c = 0;
    for (int i = 0; i < N; i++)
        if (col[i].titulo[0] == l) { printf("%s\n", col[i].titulo); c++; }
    if (c) printf("Tenho %d jogos || %c.\n", c, l);
    else   puts("Nenhum jogo tem esse parâmetro Sr Sr Wilson.");
}

void printStudio(char *s) {
    int c = 0;
    for (int i = 0; i < N; i++)
        if (!strcmp(col[i].estudio, s)) { printf("%s\n", col[i].titulo); c++; }
    if (c) printf("Tenho %d jogos || %s.\n", c, s);
    else   puts("Nenhum jogo tem esse parâmetro Sr Sr Wilson.");
}

void printConsole(char *s) {
    int c = 0;
    for (int i = 0; i < N; i++)
        if (!strcmp(col[i].console, s)) { printf("%s\n", col[i].titulo); c++; }
    if (c) printf("Tenho %d jogos || %s.\n", c, s);
    else   puts("Nenhum jogo tem esse parâmetro Sr Sr Wilson.");
}

void printColecao() {
    for (int i = 0; i < N; i++)
        printf("%s %d\n", col[i].titulo, col[i].nota);
}

int main(void) {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%s %s %s %s %d %d",
              col[i].titulo, col[i].genero, col[i].estudio,
              col[i].console, &col[i].nota, &col[i].ano);
        if      (col[i].nota > 7) puts("AWESOME! Mais um GOTY pra minha coleção!");
        else if (col[i].nota < 4) puts("Era melhor jogar mais um jogo de Mahjong.");
    }

    char cmd[20], param[50];
    while (scanf("%s", cmd) == 1) {
        if (!strcmp(cmd, "printColecao")) { printColecao(); continue; }
        scanf("%s", param);
        if      (!strcmp(cmd, "printAno"))     printAno(atoi(param));
        else if (!strcmp(cmd, "printLetra"))   printLetra(param[0]);
        else if (!strcmp(cmd, "printStudio"))  printStudio(param);
        else if (!strcmp(cmd, "printConsole")) printConsole(param);
    }

    puts("Enjoei de jogar, agora vou ver TV.");
}