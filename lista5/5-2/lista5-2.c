// Sistema de Notas da Escola CInal do Saber

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float calcular_media(const float *v, int n) {
    if (n <= 0) return 0.0f;
    float s = 0.0f;
    for (int i = 0; i < n; ++i) s += v[i];
    return s / n;
}

int maior_menor(const float *v, int n, float *maior, int *idxMaior, float *menor, int *idxMenor) {
    if (n <= 0) return -1;
    *maior = v[0]; *menor = v[0];
    *idxMaior = 0; *idxMenor = 0;
    for (int i = 1; i < n; ++i) {
        if (v[i] > *maior) { *maior = v[i]; *idxMaior = i; }
        if (v[i] < *menor) { *menor = v[i]; *idxMenor = i; }
    }
    return 0;
}

int contar_acima_media(const float *v, int n, float media) {
    int cnt = 0;
    for (int i = 0; i < n; ++i) if (v[i] > media) ++cnt;
    return cnt;
}

// Ordenação simples para float
int sort_floats(float *a, int n) {
    for (int i = 1; i < n; ++i) {
        float key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j+1] = a[j];
            --j;
        }
        a[j+1] = key;
    }
    return 0;
}

float calcular_mediana(const float *v, int n) {
    float *c = malloc(n * sizeof(float));
    if (!c) return 0.0f;
    for (int i = 0; i < n; ++i) c[i] = v[i];
    sort_floats(c, n);
    float med;
    if (n % 2 == 1) med = c[n/2];
    else med = (c[n/2 - 1] + c[n/2]) / 2.0f;
    free(c);
    return med;
}

// Ordenação simples para long long
int sort_ll(long long *a, int n) {
    for (int i = 1; i < n; ++i) {
        long long key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j+1] = a[j];
            --j;
        }
        a[j+1] = key;
    }
    return 0;
}

// Retorna 1 se houver moda unica e escreve em *moda_val

// Retorna 0 caso nao haja moda unica
int calcular_moda(const float *v, int n, float *moda_val) {
    if (n == 0) return 0;
    long long *arr = malloc(n * sizeof(long long));
    if (!arr) return 0;
    for (int i = 0; i < n; ++i) arr[i] = (long long) roundf(v[i] * 100.0f);
    sort_ll(arr, n);

    int maxCount = 1, count = 1;
    long long bestVal = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] == arr[i-1]) ++count;
        else {
            if (count > maxCount) { maxCount = count; bestVal = arr[i-1]; }
            count = 1;
        }
    }
    if (count > maxCount) { maxCount = count; bestVal = arr[n-1]; }

    // verificar unicidade
    int howManyWithMax = 0;
    count = 1;
    for (int i = 1; i < n; ++i) {
        if (arr[i] == arr[i-1]) ++count;
        else {
            if (count == maxCount) ++howManyWithMax;
            count = 1;
        }
    }
    if (count == maxCount) ++howManyWithMax;

    free(arr);

    if (maxCount == 1 || howManyWithMax != 1) return 0;
    *moda_val = ((float)bestVal) / 100.0f;
    return 1;
}

int imprimir_relatorio(const float *v, int n) {
    float med = calcular_media(v, n);
    float maior, menor; int idxMaior, idxMenor;
    maior_menor(v, n, &maior, &idxMaior, &menor, &idxMenor);
    int acima = contar_acima_media(v, n, med);
    float mediana = calcular_mediana(v, n);
    float moda_val;
    int temModa = calcular_moda(v, n, &moda_val);

    printf("Media: %.2f\n", med);
    printf("Maior nota: %.2f (aluno %d)\n", maior, idxMaior + 1);
    printf("Menor nota: %.2f (aluno %d)\n", menor, idxMenor + 1);
    printf("Acima da media: %d\n", acima);
    printf("Mediana: %.2f\n", mediana);
    if (temModa) printf("Moda: %.2f\n", moda_val);
    else printf("Moda: Nao ha moda unica\n");
    return 0;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n <= 0) return 0;
    float *notas = malloc(n * sizeof(float));
    if (!notas) return 0;
    for (int i = 0; i < n; ++i) scanf("%f", &notas[i]);

    int k;
    if (scanf("%d", &k) != 1) k = 0;
    float *novas = NULL;
    if (k > 0) {
        novas = malloc(k * sizeof(float));
        for (int i = 0; i < k; ++i) scanf("%f", &novas[i]);
    }

    printf("Relatorio inicial\n");
    imprimir_relatorio(notas, n);
    printf("\n");

    // adicionar novas notas usando realloc
    if (k > 0) {
        float *tmp = realloc(notas, (n + k) * sizeof(float));
        if (!tmp) {
            free(notas);
            free(novas);
            return 0;
        }
        notas = tmp;
        for (int i = 0; i < k; ++i) notas[n + i] = novas[i];
        n += k;
    }

    printf("Relatorio atualizado\n");
    imprimir_relatorio(notas, n);

    free(notas);
    if (novas) free(novas);
    return 0;
}
