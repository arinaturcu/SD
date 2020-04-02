#ifndef __HASH_UTILS_H
#define __HASH_UTILS_H

struct info {
    char *key;
    char *value;
    int freq;
};

struct Hashtable {
    struct info **buckets;
    int hmax; /* Nr. de bucket-uri. */
    unsigned int (*hash_function)(void*);
};

unsigned int hash_function_string(void *a);

void init_ht(struct Hashtable *ht, int hmax, unsigned int (*hash_function)(void*));

struct info* get(struct Hashtable *ht, void *key);

void put(struct Hashtable *ht, char *key, char *value);

void free_ht(struct Hashtable **ht_loc);

#endif