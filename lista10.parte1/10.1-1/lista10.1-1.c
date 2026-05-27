// Attack de Stack
#include <stdio.h>
#include <math.h>

char s[100000];
int t = 0;

void check() {
    int c = 1;
    while (c) {
        c = 0;
        if (t >= 2) {
            char a = s[t-2], b = s[t-1], n = 0;
            if ((a=='g'&&b=='b')||(a=='b'&&b=='g')) n='c';
            else if ((a=='r'&&b=='b')||(a=='b'&&b=='r')) n='m';
            else if ((a=='r'&&b=='g')||(a=='g'&&b=='r')) n='y';
            if (n) { s[t-2]=n; t--; c=1; }
        }
        if (t>=3 && s[t-3]==s[t-2] && s[t-2]==s[t-1]) { t-=3; c=1; }
    }
}

int main() {
    char ch;
    while (scanf(" %c", &ch) == 1) {
        s[t++] = ch;
        check();
        if (!t) printf("Pilha vazia!\n");
        else { for (int i=t-1;i>=0;i--) { putchar(s[i]); putchar('\n'); } }
        putchar('\n');
    }
    puts("Thank You So Much For Playing My Game!");
}