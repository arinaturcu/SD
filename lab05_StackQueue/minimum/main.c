/*  M-am folosit de o stiva auxiliara in care am pus mereu elementul minim si
 * am dat-o ca parametru in functii impreuna cu stiva principala.
 * Mi-ar fi placut sa nu o dau ca parametru, dar nu imi dau seama cum.
 */
#include <stdio.h>
#include <stdlib.h>

#include "../src/LinkedList.h"

struct Stack {
    struct LinkedList *list;
};

void init_stack(struct Stack *stack) {
    stack->list = malloc(sizeof(struct LinkedList));
    if (stack->list == NULL) {
        perror("Not enough memory to initialize the stack!");
        return;
    }

    init_list(stack->list);
}

void* peek(struct Stack *stack) {
    return stack->list->tail->data;
}

void pop(struct Stack *stack, struct Stack *aux_st) {
    struct Node *be_gone, *aux_node;

    be_gone = remove_nth_node(stack->list, 0x7fffffff);

    if (*(int*)be_gone->data == *(int*)peek(aux_st)) {
        aux_node = remove_nth_node(aux_st->list, 0x7fffffff);
        free(aux_node);
    }

    free(be_gone);
}

void push(struct Stack *stack, struct Stack *aux_st, void *new_data) {
    if (stack->list->size == 0 || *(int*)new_data < *(int*)peek(aux_st)) {
        add_nth_node(aux_st->list, 0x7fffffff, new_data);
    }
    add_nth_node(stack->list, 0x7fffffff, new_data);
}

void *get_min(struct Stack *st, struct Stack *aux_st){
    return aux_st->list->tail->data;
}

void purge_stack(struct Stack *stack) {
    free_list(&stack->list);
}

int main() {
    struct Stack *st, *aux_st;
    int num[] = {50, 40, 35, 55, 37, 20, 60, 10};

    st = malloc(sizeof(struct Stack));
    aux_st = malloc(sizeof(struct Stack));

    init_stack(st);
    init_stack(aux_st);

    printf("Minimul dupa fiecare pas:\n");
    push(st, aux_st, &num[0]);
    printf("%d\n", *(int*)get_min(st, aux_st));
    push(st, aux_st, &num[1]);
    printf("%d\n", *(int*)get_min(st, aux_st));
    push(st, aux_st, &num[2]);
    printf("%d\n", *(int*)get_min(st, aux_st));
    push(st, aux_st, &num[3]);
    printf("%d\n", *(int*)get_min(st, aux_st));
    push(st, aux_st, &num[4]);
    printf("%d\n", *(int*)get_min(st, aux_st));
    push(st, aux_st, &num[5]);
    printf("%d\n", *(int*)get_min(st, aux_st));
    pop(st, aux_st);
    printf("%d\n", *(int*)get_min(st, aux_st));
    pop(st, aux_st);
    printf("%d\n", *(int*)get_min(st, aux_st));
    push(st, aux_st, &num[6]);
    printf("%d\n", *(int*)get_min(st, aux_st));
    pop(st, aux_st);
    printf("%d\n", *(int*)get_min(st, aux_st));
    push(st, aux_st, &num[7]);
    printf("%d\n", *(int*)get_min(st, aux_st));

    purge_stack(st);
    purge_stack(aux_st);
    free(st);
    free(aux_st);

    return 0;

}