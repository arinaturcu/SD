// Copyright Arina Turcu 313CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NMAX 101

struct info {
    char *key;
    char *value;
    int freq;
};

struct Hashtable {
    struct info **buckets;
    int hmax;  // Nr. de bucket-uri.
    unsigned int (*hash_function)(void *);
};

unsigned int hash_function_string(void *a) {
    /*
     * Credits: http://www.cse.yorku.ca/~oz/hash.html
     */
    unsigned char *puchar_a = (unsigned char *)a;
    __int64_t hash = 5381;
    int c;

    while ((c = *puchar_a++))
        hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

    return hash;
}

void init_ht(struct Hashtable *ht, int hmax,
    unsigned int (*hash_function)(void *)) {
    ht->buckets = (struct info **)malloc(hmax * sizeof(struct info *));

    if (ht->buckets == NULL) {
        fprintf(stderr, "Error: Nu s-a putut aloca memorie");
        return;
    }

    for (int i = 0; i < hmax; ++i) {
        ht->buckets[i] = NULL;
    }

    ht->hmax = hmax;
    ht->hash_function = hash_function;
}

void put(struct Hashtable *ht, char *key, char *value) {
    int index;
    struct info *new, *bucket;

    index = ht->hash_function(key) % ht->hmax;
    bucket = ht->buckets[index];

    if (bucket == NULL) {
        bucket = (struct info *)malloc(sizeof(struct info));
        bucket->key = (char *)malloc(sizeof(char) * (strlen(key) + 1));
        bucket->value = (char *)malloc(sizeof(char) * (strlen(value) + 1));

        memcpy(bucket->key, key, strlen(key) + 1);
        memcpy(bucket->value, value, strlen(value) + 1);

        bucket->freq = 1;
        ht->buckets[index] = bucket;
    } else {
        if (strcmp(bucket->key, key) == 0) {
            bucket->freq++;
        } else {
            // cauta o pozitie libera
            new = ht->buckets[index + 1];

            while (new == NULL) {
                if (index >= ht->hmax) {
                    index = 0;
                }
                index++;
            }

            new = ht->buckets[index];

            new = (struct info *)malloc(sizeof(struct info));
            new->key = (char *)malloc(sizeof(char) * (strlen(key) + 1));
            new->value = (char *)malloc(sizeof(char) * (strlen(value) + 1));

            memcpy(new->key, key, strlen(key) + 1);
            memcpy(new->value, value, strlen(key) + 1);
            new->freq = 1;
            ht->buckets[index] = new;
        }
    }

    if (bucket == NULL || ht->buckets[index]->key == NULL ||
        ht->buckets[index]->value == NULL) {
        fprintf(stderr, "Error: Nu s-a putut aloca memorie");
        return;
    }
}

void free_ht(struct Hashtable **ht_loc) {
    for (int i = 0; i < (*ht_loc)->hmax; ++i) {
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

int main() {
    struct Hashtable *ht;
    struct info *data;
    char word[NMAX];
    int i;

    ht = (struct Hashtable *)malloc(sizeof(struct Hashtable));

    if (ht == NULL) {
        fprintf(stderr, "Error: Nu s-a putut aloca memorie");
        return -1;
    }

    init_ht(ht, NMAX, hash_function_string);

    while (!feof(stdin) && scanf("%s", word) == 1) {
        put(ht, word, word);
    }

    for (i = 0; i < ht->hmax; ++i) {
        data = ht->buckets[i];
        if (data != NULL) {
            printf("%s %d\n", data->value, data->freq);
        }
    }

    free_ht(&ht);

    return 0;
}
