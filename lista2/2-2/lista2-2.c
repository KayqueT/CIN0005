#include <stdio.h>

int main() {
    int n, k, p;
    if (scanf("%d" "%d" "%d", &n, &k, &p) != 3) {
        return 1;
    }
    
    // Se k for zero ou negativo, o intervalo � inv�lido
    if (k <= 0) {
        printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.\n");
        return 0;
    }
    
// Cria os arrays dinamicamente usando o tamanho exato de K
    int contagem_primos_impares[k];
    int tem_primo_impar_repetido[k];

    for (int i = 0; i < k; i++) {
        contagem_primos_impares[i] = 0;
        tem_primo_impar_repetido[i] = 0;
    }

    // O n�mero 0 marcamos como inv�lido
    tem_primo_impar_repetido[0] = 1;

    // Calcula os fatores apenas at� k
    for (long long i = 3; i < k; i += 2) {
        if (contagem_primos_impares[i] == 0) {
            
            // Marca os m�ltiplos de i
            for (long long j = i; j < k; j += i) {
                contagem_primos_impares[j]++;
            }
            
            // Marca os m�ltiplos do quadrado de i (fatores repetidos)
            long long quadrado = i * i;
            for (long long j = quadrado; j < k; j += quadrado) {
                tem_primo_impar_repetido[j] = 1;
            }
        }
    }

    int primeiro_encontrado = -1;
    int q = 0;

    // Procura os n�meros no intervalo de N at� k - 1 (antes de k)
    for (int m = n; m < k; m++) {
        if (!tem_primo_impar_repetido[m] && contagem_primos_impares[m] == p) {
            
            if (primeiro_encontrado == -1) {
                primeiro_encontrado = m;
            } else {
                q++;
            }
        }
    }

    // Output
    if (primeiro_encontrado != -1) {
        printf("%d %d\n", primeiro_encontrado, q);
    } else {
        printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.\n");
    }

    return 0;
}