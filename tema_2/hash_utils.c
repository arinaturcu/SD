#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_utils.h"

unsigned int hash_function_string(void *a) {
    /*
     * Credits: http://www.cse.yorku.ca/~oz/hash.html
     */
    unsigned char *puchar_a = (unsigned char*) a;
    unsigned long hash = 5381;
    int c;

    while ((c = *puchar_a++))
        hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

    return hash;
}

void init_ht(struct Hashtable *ht, int hmax, unsigned int (*hash_function)(void*)) {
    ht->buckets = (struct info **)malloc(hmax * sizeof(struct info*));
    
    for (int i = 0; i < hmax; ++i) {
        ht->buckets[i] = NULL;
    }
    
    ht->hmax = hmax;
    ht->hash_function = hash_function;
}

struct info* get(struct Hashtable *ht, void *key) {
    int index;
    struct info *curr_bucket;

    index = ht->hash_function(key) % ht->hmax;
    curr_bucket = ht->buckets[index];

    while (strcmp(curr_bucket->key, key) != 0) {
        curr_bucket = ht->buckets[index];
        index++;
        if (index >= ht->hmax) {
            index = 0;
        }
    }

    return curr_bucket;
}

void put(struct Hashtable *ht, char *key, char *value) {
    int index;
    struct info *new;

    index = ht->hash_function(key) % ht->hmax;

    if (ht->buckets[index] == NULL) {
        ht->buckets[index] = (struct info *)malloc(sizeof(struct info));
        ht->buckets[index]->key = (char *)malloc(sizeof(char) * (strlen(key) + 1));
        ht->buckets[index]->value = (char *)malloc(sizeof(char) * (strlen(value) + 1));

        memcpy(ht->buckets[index]->key, key, strlen(key) + 1);
        memcpy(ht->buckets[index]->value, value, strlen(value) + 1);

        ht->buckets[index]->freq = 1;

    } else {
        if (strcmp(ht->buckets[index]->key, key) == 0) {
            ht->buckets[index]->freq++;

        } else {
            /* cauta o pozitie libera */

            new = ht->buckets[index];
            while (new != NULL) {
                if (index >= ht->hmax) {
                    index = 0;
                }
                new = ht->buckets[index];
                index++;
            }

            new = (struct info *)malloc(sizeof(struct info));
            new->key = (char *)malloc(sizeof(char) * (strlen(key) + 1));
            new->value = (char *)malloc(sizeof(char) * (strlen(value) + 1));

            memcpy(new->key, key, strlen(key) + 1);
            memcpy(new->value, value, strlen(key) + 1);
            new->freq = 1;
        }
    }
}

void free_ht(struct Hashtable **ht_loc) {
    int i;

    for (i = 0; i < (*ht_loc)->hmax; ++i) {
        if ((*ht_loc)->buckets[i] != NULL) {
            free((*ht_loc)->buckets[i]->key);
            free((*ht_loc)->buckets[i]->value);
            free((*ht_loc)->buckets[i]);
            (*ht_loc)->buckets[i] = NULL;
        }
    }
    free((*ht_loc)->buckets);
    free(*ht_loc);
}
