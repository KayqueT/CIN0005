// Mapa vazio

#include <stdio.h>
#include <stdlib.h>

int main() {
    long long *arr = NULL;
    int n = 0, cap = 0;
    long long x;

    while (scanf("%lld", &x) == 1) {
        if (n == cap) {
            int newcap = cap == 0 ? 8 : cap * 2;
            long long *tmp = realloc(arr, newcap * sizeof(long long));
            if (!tmp) {
                free(arr);
                return 1;
            }
            arr = tmp;
            cap = newcap;
        }
        arr[n++] = x;
    }

    printf("Mais um bom dia de trabalho!\n");

    for (int i = 0; i < n; ++i) {
        if (arr[i] % 2 != 0) printf("%lld\n", arr[i]);
    }
    for (int i = 0; i < n; ++i) {
        if (arr[i] % 2 == 0) printf("%lld\n", arr[i]);
    }

    printf("Vou visitar esses lugares de novo... algum dia.\n");

    free(arr);
    return 0;
}
