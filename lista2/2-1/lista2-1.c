#include <stdio.h>

int main() {
    char letra;
    
    scanf(" %c", &letra);
    
    // Converte para mai�scula se o usu�rio digitar min�scula
    if (letra >= 'a' && letra <= 'z') {
        letra -= 32;
    }
    
    // Valida��o de entrada
    if (letra < 'A' || letra > 'Z') {
        return 1;
    }
    
    // Calcula quantas linhas o tri�ngulo ter�
    int total_linhas = letra - 'A' + 1;
    
    // La�o principal que percorre cada linha
    for (int i = 0; i < total_linhas; i++) {
        
        // 1. Imprime os pontos � esquerda
        for (int pontos = 0; pontos < total_linhas - i - 1; pontos++) {
            printf(".");
        }
        
        // 2. Imprime as letras em ordem crescente (ex: A, B, C)
        for (int j = 0; j <= i; j++) {
            printf("%c", 'A' + j);
        }
        
        // 3. Imprime as letras em ordem decrescente (ex: B, A)
        for (int j = i - 1; j >= 0; j--) {
            printf("%c", 'A' + j);
        }
        
        // 4. Imprime os pontos � direita
        for (int pontos = 0; pontos < total_linhas - i - 1; pontos++) {
            printf(".");
        }
        
        printf("\n"); // Pula para a pr�xima linha
    }
    
    return 0;
}