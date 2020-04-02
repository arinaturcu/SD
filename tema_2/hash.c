#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_utils.h"

#define NMAX 101

int main() {
    struct Hashtable *ht;
    struct info *data;
    char word[NMAX];
    int i;

    ht = (struct Hashtable *)malloc(sizeof(struct Hashtable));
    init_ht(ht, NMAX, hash_function_string);

    while(!feof(stdin) && scanf("%s", word) == 1) {
        put(ht, word, word);
    }

    for(i = 0; i < ht->hmax; ++i) {
        data = ht->buckets[i];
        if (data != NULL) {
            printf("%s %d\n", data->value, data->freq);
        }
    }

    free_ht(&ht);

    return 0;
}
