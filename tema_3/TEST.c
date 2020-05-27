#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct author{
    char* name;
    int64_t id;
    char* institution;  
};

struct article {
    char* title;
    char* venue;
    int year;
    struct author **authors;  
    int num_authors;
    char** fields;
    int num_fields;
    int64_t id;
    int64_t* references;
    int num_refs;
};

struct PublData {
    struct article *paper;
};

unsigned int hash_function_string(void *a) {
    /*
     * Credits: http://www.cse.yorku.ca/~oz/hash.html
     */
    unsigned char *puchar_a = (unsigned char*) a;
    unsigned int hash = 5381;
    int c;

    while ((c = *puchar_a++))
        hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

    return hash;
}

void add_paper(struct PublData* data, const char* title, const char* venue,
    const int year, const char** author_names, const int64_t* author_ids,
    const char** institutions, const int num_authors, const char** fields,
    const int num_fields, const int64_t id, const int64_t* references,
    const int num_refs) {

    data->paper = malloc(sizeof(struct article));
    
    data->paper->title        = strdup(title);
    data->paper->venue        = strdup(venue);
    data->paper->year         = year;
    data->paper->num_authors  = num_authors;
    data->paper->num_fields   = num_fields;
    data->paper->id           = id;
    data->paper->num_refs     = num_refs;

    data->paper->authors = malloc(num_authors * sizeof(struct author*));
    for (int i = 0; i < num_authors; i++) {
        data->paper->authors[i] = malloc(sizeof(struct author));

        data->paper->authors[i]->name = strdup(author_names[i]);
        data->paper->authors[i]->id = author_ids[i];
        data->paper->authors[i]->institution = strdup(institutions[i]);
    }
    
    data->paper->fields = malloc(num_fields * sizeof(char*));
    for (int i = 0; i < num_fields; i++) {
        data->paper->fields[i] = strdup(fields[i]);
    }

    data->paper->references = malloc(num_refs * sizeof(int64_t));
    for (int i = 0; i < num_refs; i++) {
        data->paper->references[i] = references[i];
    } 
}

unsigned int call_hash(void *a) {
    return hash_function_string(a);
}

int main() {
    struct PublData *data = malloc(sizeof(struct PublData));

    const char*   title = "title";
    const char*   venue = "venue";
    const int     year = 1990;
    const char*   author_names[] = {"Name Surname", "Name2 Surname2"};
    const int64_t author_ids[] = {1, 2};
    const char*   institutions[] = {"UPB", "ASE"};
    const int     num_authors = 2;
    const char*   fields[] = {"CS", "DS"};
    const int     num_fields = 2;
    const int64_t id = 7361381;
    const int64_t references[] = {12345, 54321};
    const int     num_refs = 2;

    add_paper(data, title, venue, year, author_names, author_ids, institutions, num_authors, fields, num_fields, id, references, num_refs);

    printf("%s\n", data->paper->title);
    printf("%s\n", data->paper->venue);
    printf("%d\n", data->paper->year);
    printf("%d\n", data->paper->num_authors);
    printf("%d\n", data->paper->num_fields);
    printf("%ld\n", data->paper->id);
    printf("%d\n", data->paper->num_refs);
    printf("%s -- %s\n", data->paper->authors[0]->name, data->paper->authors[1]->name);
    printf("%ld -- %ld\n", data->paper->authors[0]->id, data->paper->authors[1]->id);
    printf("%s -- %s\n", data->paper->authors[0]->institution, data->paper->authors[1]->institution);
    printf("%s -- %s\n", data->paper->fields[0], data->paper->fields[1]);
    printf("%ld -- %ld\n", data->paper->references[0], data->paper->references[1]);

    int a = 2, b = 5;
    printf("%f\n", (double)a/(double)b);

    const char *venuee = "KI";

    printf("%d\n", call_hash((void *)venuee));
    printf("%u\n", call_hash((void *)venuee));

    return 0;
}