#include <stdio.h>
#include <stdlib.h>

typedef struct No { int v; struct No *e, *d; } No;

No *novo(int v) { No *n = malloc(sizeof(No)); n->v=v; n->e=n->d=NULL; return n; }

No *inserir(No *r, int v) {
    if (!r) return novo(v);
    if (v < r->v) r->e = inserir(r->e, v);
    else if (v > r->v) r->d = inserir(r->d, v);
    return r;
}

void pre(No *r)  { if (r) { printf("%d ", r->v); pre(r->e);  pre(r->d);  } }
void em(No *r)   { if (r) { em(r->e);  printf("%d ", r->v); em(r->d);   } }
void pos(No *r)  { if (r) { pos(r->e); pos(r->d);  printf("%d ", r->v); } }

int nos(No *r)    { return r ? 1 + nos(r->e) + nos(r->d) : 0; }
int folhas(No *r) { return r ? (r->e||r->d ? folhas(r->e)+folhas(r->d) : 1) : 0; }
int altura(No *r) { if (!r) return -1; int h=altura(r->e), hd=altura(r->d); return 1+(h>hd?h:hd); }
int menor(No *r)  { return r->e ? menor(r->e) : r->v; }
int maior(No *r)  { return r->d ? maior(r->d) : r->v; }

int main() {
    No *r = NULL;
    int v;
    while (scanf("%d", &v) == 1 && v != -1) r = inserir(r, v);

    if (!r) { puts("ARVORE VAZIA"); return 0; }

    printf("PREORDEM: ");  pre(r);  puts("");
    printf("EMORDEM: ");   em(r);   puts("");
    printf("POSORDEM: ");  pos(r);  puts("");
    printf("NOS: %d\nFOLHAS: %d\nALTURA: %d\nMENOR: %d\nMAIOR: %d\n",
           nos(r), folhas(r), altura(r), menor(r), maior(r));
}