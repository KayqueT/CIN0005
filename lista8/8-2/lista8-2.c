#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef union {
    uint32_t raw;
    struct {
        uint32_t sensor_id : 10;
        uint32_t status    :  3;
        uint32_t bateria   :  1;
        int32_t  temp      : 12;
        uint32_t paridade  :  6;
    };
} Pacote;

int main(void) {
    int cap = 2, n = 0;
    Pacote *v = malloc(cap * sizeof(Pacote));

    uint32_t x;
    while (scanf("%x", &x) == 1 && x) {
        if (n == cap) v = realloc(v, (cap *= 2) * sizeof(Pacote));
        v[n++].raw = x;
    }

    for (int i = 0; i < n; i++) {
        printf("Pacote [%d] - Dado Bruto: 0x%08X\n", i + 1, v[i].raw);
        printf("  ID do Sensor : %u\n",  v[i].sensor_id);
        printf("  Status       : %u\n",  v[i].status);
        printf("  Bateria Baixa: %s\n",  v[i].bateria ? "SIM (ALERTA)" : "Nao");
        printf("  Temperatura  : %d graus\n", v[i].temp);
        printf("--------------------------------------------------\n");
    }

    free(v);
}
