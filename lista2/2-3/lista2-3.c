#include <stdio.h>
#include <stdlib.h>

int main() {
    long long X; // O n�mero dado a Xupenio
    int N;       // A quantidade de canais

    if (scanf("%lld", &X) != 1) return 1;
    if (scanf("%d", &N) != 1) return 1;

    // Vari�veis globais para armazenar a melhor op��o entre todos os canais
    long long melhor_diferenca_1 = -1;
    long long melhor_valor_1 = -1;
    int melhor_minuto_1 = -1;
    int melhor_canal_1 = -1;

    for (int c = 1; c <= N; c++) {
        long long f1, f2;
        if (scanf("%lld %lld", &f1, &f2) != 2) return 1;

        // Vari�veis locais para avaliar o canal atual
        long long melhor_valor_local = f1;
        long long melhor_diferenca_local = llabs(f1 - X);
        int melhor_minuto_local = 1;

        long long diferenca2 = llabs(f2 - X);
        
        if (diferenca2 < melhor_diferenca_local) {
            melhor_valor_local = f2;
            melhor_diferenca_local = diferenca2;
            melhor_minuto_local = 2;
        }

        long long anterior = f1;
        long long atual = f2;
        int minuto = 3;
        
        int calculando = 1;

        while (calculando) {
            long long proximo_valor = anterior + atual;
            long long proxima_diferenca = llabs(proximo_valor - X);

            if (proxima_diferenca < melhor_diferenca_local) {
                melhor_valor_local = proximo_valor;
                melhor_diferenca_local = proxima_diferenca;
                melhor_minuto_local = minuto;
            }

            if (proximo_valor > X && proxima_diferenca >= melhor_diferenca_local) {
                calculando = 0; 
            } else if (proximo_valor == atual && proximo_valor == anterior && minuto > 3) {
                calculando = 0; 
            }
            
            if (calculando) {
                anterior = atual;
                atual = proximo_valor;
                minuto++;
            }
        }

        // Compara o melhor resultado deste canal com o melhor resultado geral
        if (c == 1) {
            melhor_diferenca_1 = melhor_diferenca_local;
            melhor_valor_1 = melhor_valor_local;
            melhor_minuto_1 = melhor_minuto_local;
            melhor_canal_1 = c;
        } else {
            if (melhor_diferenca_local <= melhor_diferenca_1) {
                melhor_diferenca_1 = melhor_diferenca_local;
                melhor_valor_1 = melhor_valor_local;
                melhor_minuto_1 = melhor_minuto_local;
                melhor_canal_1 = c;
            }
        }
    }

    // L�gica para somar os algarismos e verificar o VIP
    long long valor_temporario = melhor_valor_1;
    if (valor_temporario < 0) valor_temporario = -valor_temporario; 
    int soma_digitos = 0;
    
    while (valor_temporario > 0) {
        soma_digitos += valor_temporario % 10;
        valor_temporario /= 10;
    }

    int vip = (soma_digitos > 10);

    // Sa�da final
    if (vip) {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d e com o VIP garantido!!!\n", melhor_canal_1, melhor_minuto_1);
    } else {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d, mas o ingresso VIP n�o vai rolar :(\n", melhor_canal_1, melhor_minuto_1);
    }

    return 0;
}