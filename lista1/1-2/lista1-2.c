#include <stdio.h>

// Soma dos múltiplos de k (resultado = total) no intervalo [1, n]
long long somaM(long long k, long long n) {
    long long m = n / k;
    return k * m * (m + 1) / 2;
}

int main() {
    long long N, A, B;

    scanf("%lld", &N);
    scanf("%lld %lld", &A, &B);

    // Soma de todos os naturais de 1 a N
    long long total = N * (N + 1) / 2;

    long long resultado;

    long long mmc = A * B;

    // K 
    resultado = total
                - somaM(A, N)
                - somaM(B, N)
                + somaM(mmc, N);

    printf("%lld\n", resultado);

    if (resultado % 2 == 0)
        printf("Lá ele!!!\n");
    else
        printf("Opa xupenio AULAS...\n");
    return 0;
}