// Copyright Arina Turcu 313CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int x, max, old, *freq;

    max = 0;
    freq = calloc(1, sizeof(int));

    while (!feof(stdin) && scanf("%d", &x) == 1) {
        if (x > max) {
            old = max;
            max = x;

            freq = (int *)realloc(freq, sizeof(int) * (max + 1));

            for (int j = old + 1; j <= max; ++j) {
                freq[j] = 0;
            }
        }
        freq[x]++;
    }

    for (int i = 0; i <= max; ++i) {
        if (freq[i] != 0) {
            printf("%d %d\n", i, freq[i]);
        }
    }

    free(freq);
    return 0;
}
