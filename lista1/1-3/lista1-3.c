#include <stdio.h>

int main() {
    long long T, x, y, z;

    scanf("%lld", &T);
    scanf("%lld %lld %lld", &x, &y, &z);

    long long gain    = 0;
    long long v1_f = 0, v2_f = 0, v3_f = 0;
    int invested = 0;
    int solved   = 0;

    // Tenta adicionar 0, 1, 2 ou 3 reais ao total
    for (int add = 0; add <= 3 && !solved; add++) {
        long long newT = T + add;

        // Verifica se todos os valores são inteiros (sem fração)
        if ((newT * x) % 100 == 0 &&
            (newT * y) % 100 == 0 &&
            (newT * z) % 100 == 0) {

            long long v1 = newT * x / 100;
            long long v2 = newT * y / 100;
            long long v3 = newT * z / 100;
            long long remainder = newT - v1 - v2 - v3;

            // Condição 1: sem investimento, guarda o troco
            if (add == 0) {
                gain = remainder;
                v1_f = v1; v2_f = v2; v3_f = v3;
                invested = 0;
                solved   = 1;

            // Condição 2: investe, mas só se sobrar MAIS do que gastou
            } else if (remainder > add) {
                gain = remainder - add;   // lucro líquido 
                v1_f = v1; v2_f = v2; v3_f = v3;
                invested = add;
                solved   = 1;
            }
        }
    }

     // Saída da divisão
    if (solved)
        printf("Cada homem ficou com %lld, %lld e %lld reais, respectivamente\n",
               v1_f, v2_f, v3_f);
    else
        printf("Nao foi dessa vez que Rebeka pode ajudar...\n");

    // Desafio das letras (investiu 2)
    if (invested == 2) {
        char l1, l2, l3;
        scanf(" %c %c %c", &l1, &l2, &l3);

        int soma = (l1 - 'a' + 1) + (l2 - 'a' + 1) + (l3 - 'a' + 1);
        printf("%d\n", soma);
    }

    // Desafio das idades (investiu 3)
    if (invested == 3) {
        long long a1, a2, a3;
        scanf("%lld %lld %lld", &a1, &a2, &a3);

        if (a1 % 3 == 0 || a2 % 3 == 0 || a3 % 3 == 0) {
            // Quantas parcelas de 3 cabem em cada idade → floor(age/3)
            long long soma = a1 / 3 + a2 / 3 + a3 / 3;
            printf("%lld\n", soma);
        }
    }

    // Ela começa com 3, gasta "invested" e recebe "remainder" de volta
    long long total = 3 + gain;

    if (total >= 7)
        printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n");
    else
        printf("E parece que Rebeka vai ter que voltar andando...\n");

    return 0;
}