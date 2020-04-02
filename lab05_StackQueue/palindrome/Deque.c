#include <stdio.h>
#include <stdlib.h>

#include "Deque.h"

void init_deque(struct Deque *deque) {
    deque->list = malloc(sizeof(struct LinkedList));
    if (deque->list == NULL) {
        perror("Not enough memory to initialize the stack!");
        return;
    }

    init_list(deque->list);
}

int get_size_deque(struct Deque *deque) {
    return deque->list->size;
}

int is_empty_deque(struct Deque *deque) {
    if (deque->list->size == 0){
        return 1;
    }
    return 0;
}

void* front(struct Deque *deque) {
    return deque->list->head->data;
}

void* back(struct Deque *deque) {
    return deque->list->tail->data;
}

void pop_front(struct Deque *deque) {
    struct Node *be_gone;
    be_gone = remove_nth_node(deque->list, 0);
    free(be_gone);
}

void pop_back(struct Deque *deque) {
    struct Node *be_gone;
    be_gone = remove_nth_node(deque->list, 0x7fffffff);
    free(be_gone);
}

void push_front(struct Deque *deque, void *new_data) {
    add_nth_node(deque->list, 0, new_data);
}

void push_back(struct Deque *deque, void *new_data) {
    add_nth_node(deque->list, 0x7fffffff, new_data);
}

void clear_deque(struct Deque *deque) {
    while (deque->list->size > 0) {
        pop_back(deque);
    }
}

void purge_stack(struct Deque *deque) {
    free_list(&deque->list);
}