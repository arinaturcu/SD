#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "publications.h"

#define HMAX 2000

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
    int num_cit; // numarul de paper uri care il citeaza
    int visited; // imi foloseste la dependence
};

struct publications_data {
    struct Hashtable *ht;
};

PublData* init_publ_data(void) {
    struct publications_data *data;
    data = malloc(sizeof(struct publications_data));
    data->ht = malloc(sizeof(struct Hashtable));

    init_ht(data->ht, HMAX, hash_function_int, compare_function_ints);

    return data;
}

void __remove_ht_entry(struct Hashtable *ht, void *key) {
    int index, i, j;
    struct LinkedList *buck;
    struct Node *entry;

    index = ht->hash_function(key) % ht->hmax;
    buck = &ht->buckets[index];

    entry = buck->head;
    i = 0;
    
    while (entry != NULL) {

        if ( ht->compare_function(((struct info *)entry->data)->key, key) == 0) {
            
            free( ((struct info *)entry->data)->key );

            if (((struct info *)entry->data)->value != NULL){

                free( ((struct article *)((struct info *)entry->data)->value)->title );
                free( ((struct article *)((struct info *)entry->data)->value)->venue );
                free( ((struct article *)((struct info *)entry->data)->value)->references );

                for (j = 0; j < ((struct article *)((struct info *)entry->data)->value)->num_authors; j++) {
                    free(((struct article *)((struct info *)entry->data)->value)->authors[j]->name);
                    free(((struct article *)((struct info *)entry->data)->value)->authors[j]->institution);
                    free(((struct article *)((struct info *)entry->data)->value)->authors[j]);
                }
                free(((struct article *)((struct info *)entry->data)->value)->authors);

                for (j = 0; j < ((struct article *)((struct info *)entry->data)->value)->num_fields; j++) {
                    free(((struct article *)((struct info *)entry->data)->value)->fields[j]);
                }
                free(((struct article *)((struct info *)entry->data)->value)->fields);

                free( ((struct info *)entry->data)->value );
            }
            free(entry->data);
            entry = remove_nth_node(buck, i);
            free(entry);
            
            break;
        }
        
        i++;
        entry = entry->next;
    }
}

void __free_ht(struct Hashtable *ht) {

    int i;
    struct LinkedList *buck;
    void *key;

    for (i = 0; i < ht->hmax; ++i) {
        buck = &(ht->buckets[i]);

        while (buck->size > 0) {
            
            key = ((struct info*)buck->head->data)->key;
            __remove_ht_entry(ht, key);
            
        }
    }

    free(ht->buckets);
    free(ht);
}

void destroy_publ_data(PublData* data) {
    __free_ht(data->ht);
    free(data);
}

void add_paper(PublData* data2, const char* title, const char* venue,
    const int year, const char** author_names, const int64_t* author_ids,
    const char** institutions, const int num_authors, const char** fields,
    const int num_fields, const int64_t id, const int64_t* references,
    const int num_refs) {

    struct article *paper = malloc(sizeof(struct article));
    int i;

    paper->title        = strdup(title);
    paper->venue        = strdup(venue);
    paper->year         = year;
    paper->num_authors  = num_authors;
    paper->num_fields   = num_fields;
    paper->id           = id;
    paper->num_refs     = num_refs;
    paper->num_cit      = -1;
    paper->visited      = 0;

    paper->authors = malloc(num_authors * sizeof(struct author*));
    for (i = 0; i < num_authors; i++) {
        paper->authors[i] = malloc(sizeof(struct author));

        paper->authors[i]->name        = strdup(author_names[i]);
        paper->authors[i]->id          = author_ids[i];
        paper->authors[i]->institution = strdup(institutions[i]);
    }
    
    paper->fields = malloc(num_fields * sizeof(char*));
    for (i = 0; i < num_fields; i++) {
        paper->fields[i] = strdup(fields[i]);
    }

    paper->references = malloc(num_refs * sizeof(int64_t));
    for (i = 0; i < num_refs; i++) {
        paper->references[i] = references[i];
    }

    put(data2->ht, &paper->id, sizeof(int64_t), paper);
}

static void __restore_visited(PublData *data2) {
    struct Node *curr;
    struct LinkedList *buck;
    int i, j;

    for (i = 0; i < HMAX; ++i) {
        buck = &(data2->ht->buckets[i]);
        curr = buck->head;

        while (curr != NULL) {
            ((struct article *)((struct info *)curr->data)->value)->visited = 0;
            curr = curr->next;
        }
    }
}

// returneaza numarul de paper-uri care au printre referinte pe cel dat ca parametru
static int __get_importance(PublData *data2, struct article *ref_paper) {
    struct Node *curr;
    struct LinkedList *buck;
    int num_cit = 0;
    int i, j;

    if (ref_paper == NULL) {
        return -1;
    }
    // if (ref_paper->num_cit >= 0) {
    //     return ref_paper->num_cit;
    // }

    for (i = 0; i < HMAX; ++i) {
        buck = &(data2->ht->buckets[i]);
        curr = buck->head;

        while (curr != NULL) {

            for (j = 0; j < ((struct article *)((struct info *)curr->data)->value)->num_refs; j++){
                if ( ((struct article *)((struct info *)curr->data)->value)->references[j] == ref_paper->id ) {
                    num_cit++;
                }
            }
            curr = curr->next;
        }
    }

    ref_paper->num_cit = num_cit;

    return ref_paper->num_cit;    
}

static struct article* __dependence(PublData *data, struct article *paper) {
    struct article *ref;
    struct article *smth;
    int i;
    int oldest_year = 0xfffffff;
    struct article *oldest_paper = NULL;

    struct Queue *q = malloc(sizeof(struct Queue));
    init_q(q);

    paper->visited = 1;
    enqueue(q, paper);

    while (!is_empty_q(q)) {
        smth = (struct article*)front(q);
        dequeue(q);

        for (i = 0; i < smth->num_refs; ++i)
        {
            ref = get(data->ht, &smth->references[i]);

            if (ref != NULL && ref->visited == 0) {
                ref->visited = 1;

                if (ref->year < oldest_year)
                {
                    oldest_paper = ref;
                    oldest_year = ref->year;
                }
                else if (ref->year == oldest_year)
                {
                    int ref_imp = __get_importance(data, ref);
                    int old_imp = __get_importance(data, oldest_paper);
                    if (ref_imp > old_imp)
                    {
                        oldest_paper = ref;
                    }
                    else if (ref_imp == old_imp)
                    {
                        if (ref->id < oldest_paper->id)
                        {
                            oldest_paper = ref;
                        }
                    }
                }
                enqueue(q, ref);
            }
        }
    }
    purge_q(q);
    free(q);

    __restore_visited(data);

    return oldest_paper;
}

char* get_oldest_influence(PublData* data, const int64_t id_paper) {
    char *none = "None";
    int64_t p_id = id_paper;

    struct article *paper = get(data->ht, &p_id);   
    struct article *oldest_paper = NULL;

    if (paper == NULL) {
        return none;
    }

    oldest_paper = __dependence(data, paper);

    if (oldest_paper == NULL) {
        return none;
    }

    return oldest_paper->title;
}

float get_venue_impact_factor(PublData* data, const char* venue) {
    /* TODO: implement get_venue_impact_factor */

    return 0.f;
}

int get_number_of_influenced_papers(PublData* data, const int64_t id_paper,
    const int distance) {
    /* TODO: implement get_number_of_influenced_papers */

    return -1;
}

int get_erdos_distance(PublData* data, const int64_t id1, const int64_t id2) {
    /* TODO: implement get_erdos_distance */

    return -1;
}

char** get_most_cited_papers_by_field(PublData* data, const char* field,
    int* num_papers) {
    /* TODO: implement get_most_cited_papers_by_field */

    return NULL;
}

int get_number_of_papers_between_dates(PublData* data2, const int early_date,
    const int late_date) {
    int i, nr, years;
    nr = 0;
    struct Node *curr;
    struct LinkedList *buck;
    void *key, *value2;
    struct article *articol;
    for (i = 0; i < HMAX; ++i) {
        buck = &(data2->ht->buckets[i]);
           
            if(buck->head!=NULL){
                curr=buck->head;
                while (curr != NULL) {
                    key = ((struct info*)curr->data)->key;
                    value2 = ((struct info*)curr->data)->value;
                    articol = (struct article*)value2;
                    years = articol->year;
                    if(years>=early_date && years<=late_date) {
                        nr++;
                    }
            curr = curr->next;   
            }
        }
    }
    return nr;
}

int get_number_of_authors_with_field(PublData* data, const char* institution,
    const char* field) {
    /* TODO: implement get_number_of_authors_with_field */

    return 0;
}

int* get_histogram_of_citations(PublData* data, const int64_t id_author,
    int* num_years) {
    /* TODO: implement get_histogram_of_citations */

    *num_years = 0;

    return NULL;
}

char** get_reading_order(PublData* data, const int64_t id_paper,
    const int distance, int* num_papers) {
    /* TODO: implement get_reading_order */

    *num_papers = 0;

    return NULL;
}

char* find_best_coordinator(PublData* data, const int64_t id_author) {
    /* TODO: implement find_best_coordinator */

    return NULL;
}
