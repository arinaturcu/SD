// Copyright Arina Turcu 313CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_B 2048

unsigned int hash_function_int(void *a) {
    // Credits: https://stackoverflow.com/a/12996028/7883884

    unsigned int uint_a = *((unsigned int *)a);

    uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
    uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
    uint_a = (uint_a >> 16u) ^ uint_a;
    return uint_a;
}

// calculeaza pozitia primului 1
int get_count(int remain) {
    int res = 0;

    if (remain == 0)
        return 21;

    while (!(remain & (1 << 20))) {
        remain = (remain << 1);
        res++;
    }

    return res + 1;
}

// adauga elemntul in hashtable
void add(int *map, unsigned int pos, int remain) {
    if (get_count(remain) > map[pos]) {
        map[pos] = get_count(remain);
    }
}

int get_number(int *map) {
    double Z = 0;
    double am;

    for (int i = 0; i < MAX_B; ++i) {
        Z = Z + 1 / (double)(1 << map[i]);
    }

    Z = 1 / Z;
    am = (0.7213 / (1 + 1.079 / (double)MAX_B));

    return am * MAX_B * MAX_B * Z;
}

int main(int argc, char *argv[]) {
    int map[MAX_B] = {0}, n, remain;
    int mask = (1 << 21) - 1;  // 21 biti de 1
    unsigned int hash, pos;

    if (argc == 1) {
        fprintf(stderr, "Error: No input file\n");
    }

    FILE *in = fopen(argv[1], "rt");

    // deschidere fisier
    if (in == NULL) {
        fprintf(stderr, "Error: File couldn't be opened\n");
        return -1;
    }

    // prelucrez fiecare numar in parte
    while (fscanf(in, "%d", &n) != EOF) {
        // calculeaza hash-ul
        hash = hash_function_int(&n);

        // pozitia e data de primii 11 biti
        pos = hash >> 21;
        remain = hash & mask;

        add(map, pos, remain);
    }

    printf("%d\n", get_number(map));

    return 0;
}
