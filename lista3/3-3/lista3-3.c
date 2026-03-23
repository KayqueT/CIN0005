#include <stdio.h>

int letra(char c) {
    if (c >= 'a' && c <= 'z') {
        return 1;
    }
    if (c >= 'A' && c <= 'Z') {
        return 1;
    }
    return 0;
}

// Verifica se duas fatias da string são anagramas
int sao_anagramas(char frase[], int inicio1, int tam1, int inicio2, int tam2) {
    // Anagramas precisam ter o mesmo tamanho
    if (tam1 != tam2) return 0; 
    
    // Vetor tradicional para contar as 26 letras do alfabeto
    int frequencia[26];
    for (int i = 0; i < 26; i++) {
        frequencia[i] = 0;
    }
    
    for (int i = 0; i < tam1; i++) {
        
        char c1 = (frase[inicio1 + i]);
        char c2 = (frase[inicio2 + i]);

        if (c1 >= 'A' && c1 <= 'Z') {
            frequencia[c1 - 'A']++;
        } else {
            frequencia[c1 - 'a']++;
        }
        if (c2 >= 'A' && c2 <= 'Z') {
            frequencia[c2 - 'A']--;
        } else {
            frequencia[c2 - 'a']--;
        }
        
    }
    
    // Se no final o saldo for 0 para todas as letras, é um anagrama
    for (int i = 0; i < 26; i++) {
        if (frequencia[i] != 0) return 0;
    }
    
    return 1;
}

// Imprime a palavra lendo diretamente da frase original
void imprimir_palavra(char s[], int inicio, int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%c", s[inicio + i]);
    }
}

int main() {
    char s[102];
    

    scanf("%100[^\n]", s);

    int inicios[50], tamanho[50], total = 0, i = 0, j = 0, k = 0;

    while (s[i] != '\0') {

        while (s[i] != '\0' && !letra(s[i])) {
            i++;
        }
        if (s[i] == '\0') {
            break;
        }
    // Encontrou o início de uma letra
        inicios[total] = i;
        int length = 0;

    // Letras seguidas
        while (s[i] != '\0' && letra(s[i])) {
            length++;
            i++;
        }

        tamanho[total] = length;
        total++;
    }
    
    int pares = 0;

    for (j = 0; j < total; j++) {
        for (k = j + 1; k < total; k++) {
            if (sao_anagramas(s, inicios[j], tamanho[j], inicios[k], tamanho[k])) {
                    if (pares == 0) {
                        printf("Pares de anagramas encontrados:\n");
                    }

                    imprimir_palavra(s, inicios[j], tamanho[j]);
                    printf(" e ");
                    imprimir_palavra(s, inicios[k], tamanho[k]);
                    printf("\n");

                pares++;
            }
        }
    }

    // Resultado final
    if (pares > 0) {
        printf("Total de pares: %d\n", pares);
    } else {
        printf("Nao existem anagramas na frase.\n");
    }
    
    return 0;
}