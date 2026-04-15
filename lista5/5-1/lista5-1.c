// O Vício de Krebs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int n;
    scanf("%d\n", &n);

    char *all_strings = NULL;
    int  *offsets     = malloc(n * sizeof(int));
    int  *leituras        = malloc(n * sizeof(int));

    int total_chars = 0;

    for (int i = 0; i < n; i++) {
        char buf[10001];
        if (!fgets(buf, sizeof(buf), stdin)) buf[0] = '\0';

        int ler = (int)strlen(buf);
        if (ler > 0 && buf[ler - 1] == '\n') buf[--ler] = '\0';

        offsets[i] = total_chars;
        leituras[i]    = ler;

        char *temporario = realloc(all_strings, (total_chars + ler + 1) * sizeof(char));
        all_strings = temporario;
        memcpy(all_strings + total_chars, buf, ler + 1);
        total_chars += ler;
    }

    // Mesclagem
    int max_len = 0;
    for (int i = 0; i < n; i++)
        if (leituras[i] > max_len) max_len = leituras[i];

    char *merged = malloc((total_chars + 1) * sizeof(char));
    int   mlen   = 0;

    for (int pos = 0; pos < max_len; pos++)
        for (int i = 0; i < n; i++)
            if (pos < leituras[i])
                merged[mlen++] = all_strings[offsets[i] + pos];
    merged[mlen] = '\0';

    printf("%s\n", merged);

    // Fuuu...são HA!
    char *fused = malloc((mlen + 1) * sizeof(char));
    strcpy(fused, merged);
    int flen = mlen;

    int changed = 1;
    while (changed) {
        changed = 0;
        int i = 0;
        while (i < flen - 1) {
            if (fused[i] == fused[i + 1]) {
                fused[i] = (fused[i] == 'z') ? 'a' : fused[i] + 1;
                memmove(&fused[i + 1], &fused[i + 2], flen - i - 1);
                flen--;
                fused[flen] = '\0';
                changed = 1;
                i--;
            } else {
                i++;
            }
        }
    }
    printf("%s\n", fused);
    free(all_strings);
    free(offsets);
    free(leituras);
    free(merged);
    free(fused);
    return 0;
}