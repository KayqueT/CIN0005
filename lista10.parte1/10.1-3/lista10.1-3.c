// Gerenciador de Fila de Tarefas
#include <stdio.h>
#include <stdlib.h>

typedef struct T { int id, pri; struct T *next; } T;
T *head = NULL, *tail = NULL;

void ins(int id, int pri) {
    T *t = malloc(sizeof(T));
    t->id=id; t->pri=pri; t->next=NULL;
    if (tail) tail->next=t; else head=t;
    tail=t;
}

void rem() {
    if (!head) { puts("Fila vazia"); return; }
    T *t=head; printf("Removida: id=%d prioridade=%d\n",t->id,t->pri);
    head=head->next; if (!head) tail=NULL;
    free(t);
}

void lst() {
    if (!head) { puts("Fila vazia"); return; }
    for (T *t=head; t; t=t->next) printf("id=%d prioridade=%d\n",t->id,t->pri);
}

int main() {
    char c; int id, pri;
    while (scanf(" %c",&c)==1) {
        if      (c=='I') { scanf("%d %d",&id,&pri); ins(id,pri); }
        else if (c=='R') rem();
        else if (c=='L') lst();
        else if (c=='F') break;
    }
}