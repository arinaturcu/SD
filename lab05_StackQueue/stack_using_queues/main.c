/*  Adaug mereu elementul cu enqueue in q2 si apoi iau toate 
 *  toate elementele din q1 si le pun in q2 dupa care
 *  le schimb intre ele.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/Queue.h"

struct Stack_mod {
    struct Queue *q1;
    struct Queue *q2;
};

void init_stack(struct Stack_mod *s) {
    s->q1 = malloc(sizeof(struct Queue));
    s->q2 = malloc(sizeof(struct Queue));

    init_q(s->q1);
    init_q(s->q2);
}

void push(struct Stack_mod *s, void *data) {
    void *aux;
    struct Queue *q_aux;

    enqueue(s->q2, data);

    /* dequeue tot din q1 si pun in q2 */
    while(is_empty_q(s->q1) == 0) {
        aux = front(s->q1);
        enqueue(s->q2, aux);
        dequeue(s->q1);
    }

    /* le schimb numele intre ele */
    q_aux = s->q1;
    s->q1 = s->q2;
    s->q2 = q_aux;
}

void pop(struct Stack_mod *s) {
    dequeue(s->q1);
}

void *peek(struct Stack_mod *s) {
    return front(s->q1);
}

void purge(struct Stack_mod *s) {
    free_list(&s->q1->list);
    free_list(&s->q2->list);
    free(s->q1);
    free(s->q2);
}

int main() {
    struct Stack_mod *s;
    int v[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    s = malloc(sizeof(struct Stack_mod));

    init_stack(s);

    push(s, &v[1]);
    push(s, &v[2]);
    push(s, &v[3]);
    printf("%d\n", *(int*)peek(s));
    pop(s);
    printf("%d\n", *(int*)peek(s));

    purge(s);
    free(s);

    return 0;
}