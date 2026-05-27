// Novo Sistema de Matrículas do SIGAA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node { char mat[20]; int pri; double cr; long long L, R; struct Node *next; } Node;
typedef struct { Node *front, *rear; } Queue;

void push(Queue *q, Node *n) {
    n->next = NULL;
    if (q->rear) q->rear->next = n; else q->front = n;
    q->rear = n;
}

Node *pop(Queue *q) {
    if (!q->front) return NULL;
    Node *n = q->front;
    q->front = n->next;
    if (!q->front) q->rear = NULL;
    return n;
}

void clear(Queue *q) { Node *n; while ((n=pop(q))) free(n); }

int main() {
    char cmd[20], disc[60];
    int vagas; long long clk = 1;
    Queue req = {NULL,NULL}, conf = {NULL,NULL};

    while (scanf("%s", cmd) == 1) {
        if (!strcmp(cmd,"START")) {
            scanf("%s %d", disc, &vagas);
            clk = 1; clear(&req); clear(&conf);
        } else if (!strcmp(cmd,"ADD")) {
            Node *n = malloc(sizeof(Node));
            scanf("%s %d %lf %lld %lld", n->mat, &n->pri, &n->cr, &n->L, &n->R);
            push(&req, n);
        } else if (!strcmp(cmd,"PROC")) {
            int qtd; scanf("%d", &qtd);
            while (qtd-- && req.front) {
                Node *n = pop(&req);
                if (clk < n->L) clk = n->L;
                if (clk > n->R) {
                    printf("[TIMEOUT] mat=%s | Desconectado da fila.\n", n->mat);
                    free(n);
                } else {
                    int sc = (int)round(n->cr*100)/n->pri;
                    if (vagas > 0) { printf("[ALOCADO] mat=%s | score=%d | Processado no seg: %lld\n", n->mat, sc, clk); vagas--; push(&conf, n); }
                    else           { printf("[LOTADO] mat=%s | score=%d | Processado no seg: %lld\n",  n->mat, sc, clk); free(n); }
                    clk++;
                }
            }
        } else if (!strcmp(cmd,"FIM")) {
            printf("--- LISTA OFICIAL: %s ---\n", disc);
            int p = 1; Node *n;
            while ((n=pop(&conf))) { printf("%d. Matricula: %s\n", p++, n->mat); free(n); }
        }
    }
}