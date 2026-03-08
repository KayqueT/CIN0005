#include <stdio.h>
#include <stdlib.h> // Fun��o abs()

int main() {
    // Declarar as vari�veis
    int d1, m1, a1; // Data de nascimento
    int d2, m2, a2; // Data atual
    
    // Se o Input for != 6
    if (scanf("%d/%d/%d %d/%d/%d", &d1, &m1, &a1, &d2, &m2, &a2) != 6) {
        printf("Formato de data invalido.\n");
        return 1;
    }

    // AMOR 
    int amor = ((d1 + m1 + a1 + d2 + m2 + a2) * 7) % 101;
    printf("Amor: %d%% ", amor);
    
    // Casos espec�ficos
    if (amor < 20) {
        printf("Pessimo dia para se apaixonar.\n");
    } else if (amor <= 40) {
        printf("Melhor manter o coracao <3 longe de perigo.\n");
    } else if (amor <= 69) {
        printf("Se o papo e as ideias baterem, esta liberado pensar em algo.\n");
    } else if (amor <= 80) {
        printf("Saia com o coracao aberto, mas lembre, nem toda troca de olhar em onibus e sinal de romance.\n");
    } else {
        printf("Um dia deslumbrantemente lindo para amar. Ps: Cuidado com a intensidade.\n");
    }
    
    // SORTE 
    int sorte = (((d1 + d2 + m1 + m2) * 9) + abs(a1 - a2)) % 101;
    printf("Sorte: %d%% ", sorte);
    
    // Casos espec�ficos
    if (sorte < 30) {
        printf("Nem jogue moedas pra cima hoje.");
    } else if (sorte <= 50) {
        printf("Melhor nao arriscar.");
    } else if (sorte <= 79) {
        printf("Por sua conta em risco.");
    } else if (sorte <= 90) {
        printf("Hoje vale a pena arriscar.");
    } else {
        printf("Nao tenha medo de virar cartas hoje.");
    }
    printf(" Sem tigrinho nem jogos de azar, por favor!\n");
    
    // TRABALHO 
    // abs() para evitar resultados negativos
    int c_job = (a1 + a2) - ((d1 + d2 + m1 + m2) * 8);
    int trabalho = abs(c_job) % 101;
    
    printf("Trabalho: %d%% ", trabalho);
    if (trabalho < 40) {
        printf("Hoje nao sera um dia tao proveitoso, keep calm e faca o basico.\n");
    } else if (trabalho <= 50) {
        printf("Segura a emocao, nao xinga ninguem, nao esquece de beber agua.\n");
    } else if (trabalho <= 69) {
        printf("Um dia proveitoso com certeza, leve sua simpatia consigo.\n");
    } else if (trabalho <= 84) {
        printf("Boas vibracoes hoje, chances podem estar ao seu redor.\n");
    } else {
        printf("Use do maximo de networking poss�vel hoje, dia bom para negocios.\n");
    }
    
    // COR 
    int soma_quadrados = (d1*d1) + (d2*d2) + (m1*m1) + (m2*m2) + (a1*a1) + (a2*a2);
    int cor = soma_quadrados % 11;
    
    printf("Cor: ");
    switch(cor) {
        case 0: printf("Cinza.\n"); break;
        case 1: printf("Vermelho.\n"); break;
        case 2: printf("Laranja.\n"); break;
        case 3: printf("Amarelo.\n"); break;
        case 4: printf("Verde.\n"); break;
        case 5: printf("Azul.\n"); break;
        case 6: printf("Roxo.\n"); break;
        case 7: printf("Marrom.\n"); break;
        case 8: printf("Rosa.\n"); break;
        case 9: printf("Preto.\n"); break;
        case 10: printf("Branco.\n"); break;
    }

    return 0;
}