#include <stdio.h>

typedef union {
    unsigned char raw;
    struct {
        unsigned char erro   : 1;
        unsigned char modo   : 3;
        unsigned char leitura: 4;
    };
} Sensor;

int main(void) {
    Sensor s;
    unsigned int x;
    while (scanf("%u", &x) == 1) {
        s.raw = x;
        printf("Byte bruto: %u | Erro: %u | Modo: %u | Leitura: %u\n",
               s.raw, s.erro, s.modo, s.leitura);
    }
}
